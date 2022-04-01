/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 14:36:09 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/31 14:58:25 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

int main()
{
    struct timeval start;
    struct timeval end;
    
    printf("start_time: %lld\n", current_timestamp());
    gettimeofday(&start, NULL);
    sleep(1);
    gettimeofday(&end, NULL);
    printf("end_time:   %lld\n", current_timestamp());

    return 0;
}
