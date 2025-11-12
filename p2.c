#include <stdio.h>
#include <string.h>

    int main(){

        char direction[6], yesNo[4], leftRight[6], fastSlow[5], buildDestroy[8], sunnyCloudy[7], bigSmall[6], color[6], upDown[5], easyHard[5], leftCenterRight[7], openClosed[7];
        int num, r;

        printf("north, south, east, or west: ");
        scanf("%5s", direction);

        if(strcmp(direction, "north") == 0) {
            printf("enter a positive integer: ");
            r = scanf("%99d", &num);
            if(r == 1){
                if (num % 2 == 0) {
                    printf("yes or no: ");
                    scanf("%3s", yesNo);
                        if (strcmp(yesNo, "yes") == 0) {
                            printf("lake\n");
                        }
                        else {
                            printf("pool\n");
                        }
                }
                else {
                  printf("beach\n");
                }
            }

        }
        if (strcmp(direction, "south") == 0) {
            printf("left or right: ");
            scanf("%5s", leftRight);
                if (strcmp(leftRight, "right") == 0) {
                    printf("fast or slow: ");
                    scanf("%4s", fastSlow);
                        if (strcmp(fastSlow, "slow") == 0) {
                            printf("big or small: ");
                            scanf("%5s", bigSmall);
                                if (strcmp(bigSmall, "big") == 0) {
                                    printf("run\n");
                                }
                                else {
                                    printf("walk\n");
                                }
                        }
                        else {
                            printf("bike\n");
                        }
                }
                else {
                    printf("jog\n");
                }
        }
        if (strcmp(direction, "east") == 0) {
            printf("red, white, or gray: ");
            scanf("%5s", color);
                if (strcmp(color, "red") == 0) {
                    printf("yes or no: ");
                    scanf("%3s", yesNo);
                        if (strcmp(yesNo, "no") == 0) {
                            printf("up or down: ");
                            scanf("%4s", upDown);
                                if (strcmp(upDown, "up") == 0){
                                    printf("top-rope\n");
                                }
                                else {
                                    printf("boulder\n");
                                }
                        }
                        else {
                            printf("tree-climb\n");
                        }
                }
                else if (strcmp(color, "white") == 0) {
                    printf("easy or hard: ");
                    scanf("%4s", easyHard);
                        if (strcmp(easyHard, "easy") == 0) {
                            printf("longboard\n");
                        }
                        else {
                            printf("workout\n");
                        }
                }
                else {
                    printf("left, center, or right: ");
                    scanf("%6s", leftCenterRight);
                        if (strcmp(leftCenterRight, "left") == 0) {
                            printf("build or destroy: ");
                            scanf("%7s", buildDestroy);
                                if (strcmp(buildDestroy, "build") == 0)
                                    printf("hike\n");
                                else 
                                    printf("spelunk\n");
                        }
                        if (strcmp(leftCenterRight, "center") == 0) {
                            printf("open or closed: ");
                            scanf("%6s", openClosed);
                                if (strcmp(openClosed, "open") == 0) {
                                    printf("zoo\n");
                                }
                                else 
                                    printf("aquarium\n");
                        }
                        if (strcmp(leftCenterRight, "right") == 0){
                            printf("museum\n");
                        }


                }
                }
        if (strcmp(direction, "west") == 0) {
            printf("enter an integer: ");
            r = scanf("%99d", &num);
                if(r == 1) {
                    if (num < 0) {
                        printf("sunny or cloudy: ");
                        scanf("%6s", sunnyCloudy);
                            if (strcmp(sunnyCloudy, "sunny") == 0) {
                                printf("tennis\n");
                            }
                            else 
                                printf("racquetball\n");
                    }
                    else
                        printf("frisbee\n");
                }
        }

        return 0;
    }