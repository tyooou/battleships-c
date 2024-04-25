#include <stdio.h>


void WallStreetBet(double *prices, int length){
    int i, j;
    int max_buy = 0;
    int max_sell = 0;

    for (i = 0; i < length-1; i++) {
        for (j = i+1; j < length; j++) {
            if (prices[j] - prices[i] > prices[max_sell] - prices[max_buy]) {
                max_buy = j;
                max_sell = i;
            } else if (prices[j] - prices[i] == prices[max_sell] - prices[max_buy]) {
                if (j - i < max_sell - max_buy) {
                    max_buy = j;
                    max_sell = i;
                }
            }
        }
    }
    printf("%d, %d=====D", max_buy, max_sell);
}


int main(void) {
    double prices[10] = {19.00, 19.00, 18.80, 19.00, 18.95, 18.85, 18.80, 18.85, 18.90, 19.00};
    WallStreetBet(prices, 10);
}