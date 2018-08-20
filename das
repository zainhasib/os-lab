int i, last = 0;
    int new_time = 0;
    for(i=0; i<5; i++) {
        output[i].pid = process[i].pid;
        new_time = process[i].at > last ? process[i].at : last; 
        output[i].st = new_time;
        output[i].end = new_time + process[i].bt;
        last = output[i].end;
    }