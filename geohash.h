#include "./geohash_h.h"

#ifndef GEOHASH_H
#define GEOHASH_H
char *base32_encode(char *str)
{
    int j=0;
    int length = strlen(str);
    static char base32_str[10];

    for(int i=0; i<length; i++) {
        if((i+1)%5==0) {
            int sum = ((str[i]-'0')*1) + ((str[i-1]-'0')*2) + ((str[i-2]-'0')*4) + ((str[i-3]-'0')*8) + ((str[i-4]-'0')*16); 
            base32_str[j] = base32_alphabet[sum];
            j++;
        }
    }
    efree(str);
    return base32_str;
}

char *lon_lat_to_binary(double lon, double lat, int precision)
{
    double lon_l = -180.0, lon_r = 180.0;
    double lat_l = -90.0, lat_r = 90.0;

    int  arr_length = precision * 5;
    int  bit_length = arr_length / 2;

    char lon_bits[bit_length],lat_bits[bit_length];

    for(int i=0; i<bit_length;i++) {
        double lon_mid = (lon_l+lon_r)/2;
        double lat_mid = (lat_l+lat_r)/2;

        if(lon-lon_mid>=0){
            lon_bits[i] = '1';
            lon_l = lon_mid;
        } else{
            lon_bits[i] = '0';
            lon_r = lon_mid;
        }
        if(lat-lat_mid>=0){
            lat_bits[i] = '1';
            lat_l = lat_mid;
        } else{
            lat_bits[i] = '0';
            lat_r = lat_mid;
        }

    }

    char *base32_bits = (char*)emalloc(sizeof(char)*arr_length);
    for(int j=0;j<arr_length; j++) {
        if((j+1)%2==1) {
            base32_bits[j] = lon_bits[(j+1)/2];
        } else{
            base32_bits[j] = lat_bits[j/2];
        }
    }

    return base32_bits;

}

double * binary_to_lon_Lat(int *bin, size_t bin_length)
{
    size_t l = bin_length/2;
    int lon_arr[l], lat_arr[l];

    double latM,lonM;
    static double result[2];
    double lonL = -180.0, lonR = 180.0;
    double latL = -90.0, latR = 90.0;

    for(int i=0;i<bin_length;i++) {
        if( (i+1)%2==1) {
            lon_arr[(i+1)/2] = bin[i];
        } else{
            lat_arr[i/2] = bin[i];
        }
    }

    for(int j=0; j<l; j++) {
        if(lat_arr[j]==1) {
              latM = (latL+latR)/2.0;
              latL = latM;  
        } else{
              latM = (latL+latR)/2.0;
              latR = latM;  
        }

        if(lon_arr[j]==1) {
              lonM = (lonL+lonR)/2.0;
              lonL = lonM;  
        } else{
              lonM = (lonL+lonR)/2.0;
              lonR = lonM;  
        }
    }
 
     result[0] = lonM;
     result[1] = latM;
     free(bin);
     
     return result;
}


double * char_to_binary(char *str, size_t put_str_length)
{
    size_t base32_length = sizeof(base32_alphabet)/sizeof(char);
    size_t bin_length = 5*put_str_length;
    int *arr = (int *)malloc(sizeof(int) * bin_length);
    int count = 0;
    double *res;

    for(int i=0; i<put_str_length; i++) {
        for(int j=0; j<base32_length; j++) {
            if( base32_alphabet[j] == str[i] ) {
                for(int f=5;f>0;f--) {
                    arr[count] = j>>(f-1)&1;
                    count++;
                }
            }
        }
    }
    res = binary_to_lon_Lat(arr, bin_length);

    return res;
}
#endif
