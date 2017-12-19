#include <queue>
#include <cstdlib>
#include <vector>
#include <cstdio>

enum InstructionType {
  set,
  add,
  mul,
  mod,
  jgz,
  snd,
  rcv
};

enum OperandType {
  Reg,
  Imm,
  None
};


struct Operand {
  OperandType type;
  int op;

  Operand() 
    : type(None) {}

  Operand(int i)
    : type(Imm)
    , op(i) {}

  Operand(char r)
    : type(Reg)
    , op(int(r-'a')) { }
};


struct Instruction {
  InstructionType type;
  Operand a;
  Operand b = None;
};


int64_t get(int64_t const *regs, Operand const& op) {
  if(op.type == Reg) {
    return regs[op.op];
  } else {
    return op.op;
  }
  abort();
}


void set_reg(int64_t *regs, Operand const& op, int64_t value) {
  if(op.type != Reg) abort();
  regs[op.op] = value;
}


enum State {
  Running,
  Waiting,
  Terminated
};


struct Process {
  std::vector<Instruction> const& code;
  std::queue<int64_t> recv_queue;
  std::queue<int64_t> *send_queue;
  int64_t regs[26] = {0};
  int pc = 0;
  int id;
  int sent = 0;

  Process(int id, std::vector<Instruction> const& code) 
    : code(code)
    , id(id) {
    regs['p'-'a'] = id;
  }

  void run() {
    if(pc < 0 || pc >= code.size()) {
      state = Terminated;
    }
    state = Running;
    for(;;) {
      auto const& instr = code[pc];
      switch(instr.type) {
      case snd:
        //sound = get(regs, instr.a);
        ++sent;
        send_queue->push(get(regs, instr.a));
        break;

      case set:
        set_reg(regs, instr.a, get(regs, instr.b));
        break;

      case add:
        set_reg(regs, instr.a, get(regs, instr.a) + get(regs, instr.b));
        break;

      case mul:
        set_reg(regs, instr.a, get(regs, instr.a) * get(regs, instr.b));
        break;

      case mod:
        set_reg(regs, instr.a, get(regs, instr.a) % get(regs, instr.b));
        break;

      case jgz:
        if(get(regs, instr.a) > 0) {
          pc += get(regs, instr.b) - 1;
        }
        break;

      case rcv:
        if(recv_queue.empty()) {
          state = Waiting;
          return;
        }

        set_reg(regs, instr.a, recv_queue.front());
        recv_queue.pop();

        break;
      }
      ++pc;
    }
  }


  bool runnable() const {
    return (state == Running) || (state == Waiting && !recv_queue.empty());
  }

  State state = Running;
};


int main(int argc, char ** argv) {
  std::vector<Instruction> code = {
    {set, 'i',      31},
    {set, 'a',       1},
    {mul, 'p',      17},
    {jgz, 'p',  'p'   },
    {mul, 'a',       2},
    {add, 'i',      -1},
    {jgz, 'i',      -2},
    {add, 'a',      -1},
    {set, 'i',     127},
    {set, 'p',     680},
    {mul, 'p',    8505},
    {mod, 'p',  'a'   },
    {mul, 'p',  129749},
    {add, 'p',   12345},
    {mod, 'p',  'a'   },
    {set, 'b',  'p'   },
    {mod, 'b',   10000},
    {snd, 'b'         },
    {add, 'i',      -1},
    {jgz, 'i',      -9},
    {jgz, 'a',       3},
    {rcv, 'b'         },
    {jgz, 'b',      -1},
    {set, 'f',       0},
    {set, 'i',     126},
    {rcv, 'a'         },
    {rcv, 'b'         },
    {set, 'p',  'a'   },
    {mul, 'p',      -1},
    {add, 'p',  'b'   },
    {jgz, 'p',       4},
    {snd, 'a'         },
    {set, 'a',  'b'   },
    {jgz,  1,        3},
    {snd, 'b'         },
    {set, 'f',       1},
    {add, 'i',      -1},
    {jgz, 'i',     -11},
    {snd, 'a'         },
    {jgz, 'f',     -16},
    {jgz, 'a',     -19}
  };

  Process processes[] = {
    {0, code},
    {1, code}
  };
  processes[0].send_queue = &processes[1].recv_queue;
  processes[1].send_queue = &processes[0].recv_queue;

  for(;;) {
    if(!(processes[0].runnable() || processes[1].runnable())) {
      break;
    }

    for(int i=0; i < 2; ++i) {
      if(processes[i].runnable()) {
        processes[i].run();
      }
    }
  }

  printf("%d\n", processes[1].sent);

}
