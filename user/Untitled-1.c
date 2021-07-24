
    //Run the requested working directory
    //if(ecmd->argv[0] == 0)
      //exit(1);    
    //exec(ecmd->argv[0], ecmd->argv);

    ///If didn't work, run the directories specified by PATH file
    
    
    read(path_fd, &buffer, buf_size);
    char* ptr = buffer;
    char* dots_ptr;
    while((dots_ptr = strchr(ptr, ':'))){
        *dots_ptr = '\0';
        exec(ptr, ecmd->argv);
        ptr = dots_ptr + 1;
    }
    fprintf(2, "exec %s failed\n", ecmd->argv[0]);
    break;


    //backup
    ecmd = (struct execcmd*)cmd;
    if(ecmd->argv[0] == 0)
      exit(1);    
    exec(ecmd->argv[0], ecmd->argv);
    int path_fd;
    char buffer[buf_size];
    char* str;
    path_fd= open("/path",O_RDWR);
    if(path_fd<0)
    {
      path_fd=open("/path",O_CREATE|O_RDWR);
      str= "/:/user/:";
      write(path_fd,str,strlen(str));
    }
    
    char* ptr = buffer;
    read(path_fd, ptr, buf_size);
    char* dots_ptr;
    while((dots_ptr = strchr(ptr, ':'))){
        *dots_ptr = '\0';
        int length = strlen(ptr);
        char cpy[length];
        strcpy(cpy, ptr);
        ecmd->argv[0] = cpy;
        exec(ecmd->argv[0], ecmd->argv);
        ptr = dots_ptr + 1;
    }
    fprintf(2, "exec %s failed\n", ecmd->argv[0]);



    //fucking working
    int path_fd=3;
    char buffer[2000];
    char* str;="hellpo";
    buffer[0]='1';
    if(ecmd->argv[0] == 0)
      exit(1);    
    exec(ecmd->argv[0], ecmd->argv);
    
    //buffer[0]='c';
    
    //path_fd= open("/path",O_RDWR);
    fprintf(2,"%d",path_fd);
    fprintf(2,"%c",buffer[0]);
    fprintf(2,"%s",str);
    //*buffer="hello";
    break;