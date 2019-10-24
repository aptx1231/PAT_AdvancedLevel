#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct node {
    int id;
    int arriveTime;
    int startTime;
    int serveTime;
    int waitTime;
    int isVip;
    int tableId;
    node(int id_ = 0, int ar = 0, int se = 0, int iv = 0, int st = 0, int wt = 0, int ti = -1) :
            arriveTime(ar), startTime(st), serveTime(se), isVip(iv), tableId(ti), id(id_), waitTime(wt) {}
};

struct table {
    int endTime;
    int vip;
    int num;
    //结束时间最早是8点
    table (int et=8*60*60, int vi=0, int nu=0) : endTime(et), vip(vi), num(nu) {}
} tables[105];

int com(struct node & t1, struct node & t2) {
    return t1.arriveTime < t2.arriveTime;
}

int com2(struct node & t1, struct node & t2) {
    return t1.startTime < t2.startTime;
}

int trans(char time[]) {
    int h = (time[0]-'0')*10+(time[1]-'0');
    int m = (time[3]-'0')*10+(time[4]-'0');
    int s = (time[6]-'0')*10+(time[7]-'0');
    return h*60*60+m*60+s;
}

void showTime(int time) {
    int h = time/3600;
    time %= 3600;
    int m = time / 60;
    time %= 60;
    int s = time / 1;
    printf("%02d:%02d:%02d ", h, m, s);
}

int main() {
    int n;
    cin >> n;
    vector<node> que;
    char time[20];
    int serve;
    int isVip;
    for (int i=0;i<n;i++) {
        scanf("%s %d %d", time, &serve, &isVip);
        if (serve > 120) {   //最多2小时 即120分钟  超时需要压缩时间
            serve = 120;
        }
        que.push_back(node(i, trans(time), serve*60, isVip));
    }
    int m,k;
    cin >> k >> m;
    while (m--) {
        int tmp;
        cin >> tmp;
        tables[tmp].vip = 1;
    }
    sort(que.begin(), que.end(), com);
    for (vector<node>::iterator it = que.begin(); it != que.end(); ) {
        int minEndTime = 21*60*60;
        int poi = 0;
        //找最早结束的服务台 
        for (int i=1;i<=k;i++) {
            if (tables[i].endTime < minEndTime) {
                minEndTime = tables[i].endTime;
                poi = i;
            }
        }
        if (minEndTime == 21*60*60) {  //所有服务器最早结束的时间都超过21点 后边的顾客就不能被服务了
            break;
        }
        if (tables[poi].vip) {  //最早结束的是vip桌
            //先看当前时间minEndTime，队列中有没有vip
            int flag = 1;
            for (vector<node>::iterator it_cur = it; it_cur != que.end() && it_cur->arriveTime <= minEndTime; it_cur++) {
                if (it_cur->isVip && it_cur->tableId == -1) {
                    it_cur->tableId = poi;
                    if (minEndTime < it_cur->arriveTime) {
                        it_cur->startTime = it_cur->arriveTime;
                        it_cur->waitTime = 0;
                    }
                    else {
                        it_cur->startTime = minEndTime;
                        it_cur->waitTime = (minEndTime - it_cur->arriveTime);
                    }
                    tables[poi].endTime = it_cur->startTime + it_cur->serveTime;
                    if (it_cur->startTime < 21*60*60) {
                        tables[poi].num++;
                    }
                    flag = 0;  //找到了vip 此时it不能++
                    break;
                }
            }
            if (flag) {  //没有找到vip 则选择第一个人
                it->tableId = poi;
                if (minEndTime < it->arriveTime) {
                    it->startTime = it->arriveTime;
                    it->waitTime = 0;
                }
                else {
                    it->startTime = minEndTime;
                    it->waitTime = (minEndTime - it->arriveTime);
                }
                tables[poi].endTime = it->startTime + it->serveTime;
                if (it->startTime < 21*60*60) {
                    tables[poi].num++;
                }
                it++;
            }
        }
        else {  //最早结束的不是vip桌
            if (it->isVip) {  //第一个人是vip 应该优先选择vip桌 先去找当前时间it->arriveTime有没有vip桌
                if (it->tableId == -1) {  //没有被分配过桌子的vip 因为vip可能在之前有vip桌空闲时 直接被服务了
                    int vipTable = -1;
                    for (int i=1;i<=k;i++) {  //结束时间要在当前人的到达时间之前
                        if (tables[i].vip && tables[i].endTime <= it->arriveTime) {
                            vipTable = i;
                            break;
                        }
                    }
                    if (vipTable != -1) {  //找到vip桌了
                        it->tableId = vipTable;
                        poi = vipTable;  //为了后边可以合在一起写
                    }
                    else {  //没有vip桌
                        it->tableId = poi;
                    }
                }
                else {  //队首是一个被服务过的vip 直接越过
                    it++;
                    continue;
                }
            }
            else {  //第一个人也不是vip 直接分配
                it->tableId = poi;
            }
            if (minEndTime < it->arriveTime) {
                it->startTime = it->arriveTime;
                it->waitTime = 0;
            }
            else {
                it->startTime = minEndTime;
                it->waitTime = (minEndTime - it->arriveTime);
            }
            tables[poi].endTime = it->startTime + it->serveTime;
            if (it->startTime < 21*60*60) {
                tables[poi].num++;
            }
            it++;
        }
    }
    sort(que.begin(), que.end(), com2);
    for (int i=0;i<que.size();i++) {
    	//限制在8-21点之间 21点前没有执行到的人的startTime是初始值0 不能输出 
        if (que[i].startTime >= 8*60*60 && que[i].startTime < 21*60*60) {
            showTime(que[i].arriveTime);
            showTime(que[i].startTime);
            if ((que[i].startTime - que[i].arriveTime) % 60 >= 30) {
                printf("%d\n", (que[i].startTime - que[i].arriveTime)/60+1);
            }
            else {
                printf("%d\n", (que[i].startTime - que[i].arriveTime)/60);
            }
        }
    }
    for (int i=1;i<=k;i++) {
        printf("%d", tables[i].num);
        if (i != k) {
            printf(" ");
        }
    }
    return 0;
}
