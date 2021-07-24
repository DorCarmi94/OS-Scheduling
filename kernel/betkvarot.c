 if(shouldPrint==0)
      {
        //printf("FCFS scheduler");
        shouldPrint=1;
      }

      for(p = proc; p < &proc[NPROC]; p++) {
        acquire(&p->lock);
        while(p->state == RUNNABLE) {
          // Switch to chosen process.  It is the process's job
          // to release its lock and then reacquire it
          // before jumping back to us.
          p->state = RUNNING;
          c->proc = p;
          swtch(&c->context, &p->context);

          // Process is done running for now.
          // It should have changed its p->state before coming back.
          c->proc = 0;
        }
        release(&p->lock);
      }