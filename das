int i, last = 0;
    int new_time = 0;
    for(i=0; i<5; i++) {
        output[i].pid = process[i].pid;
        new_time = process[i].at > last ? process[i].at : last; 
        output[i].st = new_time;
        output[i].end = new_time + process[i].bt;
        last = output[i].end;
    }


    process[filter[0].pid].complete = 1;
    output[out].pid = filter[0].pid;
    int max_time = filter[0].at > last ? filter[0].at : last;
    output[out].st = max_time;
    current_time = output[out].end = max_time + filter[0].bt;
    out++;