#include<stdio.h>
#include<stdlib.h>
struct packet {
    int time;
    int size;
};
int main () {
    int i, n, k = 0;
    int bucket_size, current_bucket, output_rate;
    printf ("Enter the number of packets: ");
    scanf ("%d", &n);

    struct packet p[n];
    
    printf ("\nEnter the packets in the order of their arrival time: \n");
    for (i = 0; i < n; i++) {
        printf ("Enter the time and size of packet %d: ", i+1);
        scanf ("%d %d", &p[i].time, &p[i].size);
    }
    
    printf ("\nEnter the bucket size: ");
    scanf ("%d", &bucket_size);  
    printf ("Enter the output rate: ");
    scanf ("%d", &output_rate);
    int max_time = p[n - 1].time; 
    i = 0; 
    current_bucket = 0;
    
    while (i <= max_time || current_bucket != 0) {
        printf("\nAt time %d", i);  
        if (k < n && p[k].time == i) {  
            if (bucket_size >= current_bucket + p[k].size) {
                current_bucket = current_bucket + p[k].size;
                printf("\n%d byte packet is inserted", p[k].size);
            } else {
                printf("\n%d byte packet is discarded", p[k].size);
            }
            k++; 
        }
        if (current_bucket == 0) {
            printf("\nNo packets to transmit");
        } else {
            if (current_bucket >= output_rate) {
                current_bucket = current_bucket - output_rate;
                printf("\n%d bytes transferred", output_rate);
            } else {
                printf("\n%d bytes transferred", current_bucket);
                current_bucket = 0;
            }
        }
            printf("\nPackets in the bucket: %d byte(s)\n", current_bucket);
           i++; 
    }
    return 0;
}
