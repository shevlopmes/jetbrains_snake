#include<iostream>
#include<vector>
#include<string>
using namespace std;
bool sendSignal(string command, int& x, int& y, int& stepNum) {
    stepNum++;
    bool flag = false;
    if(command == "RIGHT") {
        x++;
        flag=true;
    }
    if(command == "DOWN") {
        y--;
        flag = true;
    }
    if(command == "UP") {
        y++;
        flag = true;
    }
    if(command == "LEFT") {
        x--;
        flag = true;
    }
    if(!flag) {
        cerr << "Unknown command in sendSignal" << endl;
        exit(1);
    }
    return false;
}
int main() {
    int x = 1, y = 1, stepNum = 0, s = 1;
    //524288 = 2^19
    while(s <= 524288) {
        if(x==1) {
            // go to the starting position
            while(y < 2*s) {
                if(sendSignal("UP",x,y,stepNum)) {
                    cout << "Win!";
                    return 0;
                }
            }
            //implement algorithm
            while(y>1) {
                //check if snake is at leftmost green cell in row
                if(x==1 || (x-1)*y <= s) {
                    //find the rightmost cell such that the cell under is green, if y!= 2
                    //Otherwise find the leftmost
                    int target = x;
                    if(y!=2) {
                        for(;;target++) {
                            if(target*(y-1) > 2*s) {
                                target--;
                                break;
                            }
                        }
                    }
                    else {
                        for(;;target++) {
                            if(target*(y-1) <= 2*s && target*(y-1)>s) {
                                break;
                            }
                        }
                    }
                    //go to the target
                    while(x<target) {
                        if(sendSignal("RIGHT",x,y,stepNum)) {
                            cout << "Win!";
                            return 0;
                        }
                    }
                }
                else {
                    //find the leftmost green cell in row
                    int target = x;
                    for(;;target--) {
                        if(target*y <= s) {
                            target++;
                            break;
                        }
                    }
                    //go to the target
                    while(x>target) {
                        if(sendSignal("LEFT",x,y,stepNum)) {
                            cout << "Win!";
                            return 0;
                        }
                    }
                }
                //in both cases go 1 unit down
                if(sendSignal("DOWN",x,y,stepNum)) {
                    cout << "Win!";
                    return 0;
                }
            }
            //on the lowest row just go right to (2S,1)
            while(x<2*s) {
                if(sendSignal("RIGHT",x,y,stepNum)) {
                    cout << "Win!";
                    return 0;
                }
            }
        }
        else {
            // go to the starting position
            while(x < 2*s) {
                if(sendSignal("RIGHT",x,y,stepNum)) {
                    cout << "Win!";
                    return 0;
                }
            }
            //implement algorithm
            while(x>1) {
                //check if snake is at the lowest green cell in a column
                if(y==1 || x*(y-1) <= s) {
                    //find the highest cell such that the cell to the left is green, if x != 2.
                    //Otherwise find the lowest one.
                    int target = y;
                    if(x!=2) {
                        for(;;target++) {
                            if(target*(x-1) > 2*s) {
                                target--;
                                break;
                            }
                        }
                    }
                    else {
                        for(;;target++) {
                            if(target*(x-1) <= 2*s && target*(x-1)>s) {
                                break;
                            }
                        }
                    }
                    //go to the target
                    while(y<target) {
                        if(sendSignal("UP",x,y,stepNum)) {
                            cout << "Win!";
                            return 0;
                        }
                    }
                }
                else {
                    //find the lowest green cell in column
                    int target = y;
                    for(;;target--) {
                        if(target*x <= s) {
                            target++;
                            break;
                        }
                    }
                    //go to the target
                    while(y>target) {
                        if(sendSignal("DOWN",x,y,stepNum)) {
                            cout << "Win!";
                            return 0;
                        }
                    }
                }
                //in both cases go 1 unit left
                if(sendSignal("LEFT",x,y,stepNum)) {
                    cout << "Win!";
                    return 0;
                }
            }
            //on the leftmost column just go up to (1,2S)
            while(y<2*s) {
                if(sendSignal("UP",x,y,stepNum)) {
                    cout << "Win!";
                    return 0;
                }
            }
        }
        s*=2;
    }
    cout << stepNum;
}
