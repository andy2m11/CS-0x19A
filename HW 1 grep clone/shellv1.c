      child_pid = fork();
      if(child_pid == -1)
      {
	 err_sys("fork");
      }
      if(child_pid == 0) /* Child */
      {
	 setpgid(0,0);
	 if(execvp(argv[0], argv) == -1)
	 {
	    err_sys("execvp");
	 }
      }
      else /* Parent */
      {
	 setpgid(child_pid, child_pid);
	 if(wait(NULL) == -1)
	 {
	    err_sys("wait");
	 }
	 free(argv);
      }
