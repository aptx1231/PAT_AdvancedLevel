#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//anyone comes too late (at or after 17:00:01) will not be served nor counted into the average.
//17:00:01才到达的无法接受服务 只要是17:00:00及之前到达的都能得到服务 
//不是说顾客一直等到17:00:00但还没接收到服务，就不服务了

struct node {
    int arriveTime;
    int startTime;
    int serveTime;
    int waitTime;
    node(int ar = 0, int se = 0, int st = 0, int wt = 0) :
            arriveTime(ar), startTime(st), serveTime(se), waitTime(wt) {}
};

int tables[105];  //窗口结束时间 

int com(struct node & t1, struct node & t2) {
    return t1.arriveTime < t2.arriveTime;
}

int trans(char time[]) {
    int h = (time[0]-'0')*10+(time[1]-'0');
    int m = (time[3]-'0')*10+(time[4]-'0');
    int s = (time[6]-'0')*10+(time[7]-'0');
    return h*60*60+m*60+s;
}

int main() {
	int n,k;
	cin >> n >> k;
	//窗口时间初始化到8点 在此之前到达的人 就得等待 因为窗口最早结束时间是8点 
	for (int i=1;i<=k;i++) {
	    tables[i] = 8*60*60;
	}
	vector<node> que;
	char arrive[15];
	int servicetime, arrivetime;
	for (int i=0;i<n;i++) {
		cin >> arrive >> servicetime;
		if (servicetime > 60) {
			servicetime = 60;
		}
		arrivetime = trans(arrive);
		if (arrivetime <= 17*60*60) {  //只考虑17:00之前到达的
			que.push_back(node(arrivetime, servicetime*60));
		} //que中所有人都得服务完 
	}
	sort(que.begin(), que.end(), com);
    long long total = 0;
    int cnt = 0;
	for (int i=0; i<que.size(); i++) {  //方法就是按顺序给每个顾客分配最早结束的窗口 
        int minEndTime = 1<<30;
        int poi = 0;
        //找最早结束的服务台
        for (int j=1;j<=k;j++) {
            if (tables[j] < minEndTime) {
                minEndTime = tables[j];
                poi = j;
            }
        }
        if (minEndTime < que[i].arriveTime) {  //顾客来的晚 
            que[i].startTime = que[i].arriveTime;
            que[i].waitTime = 0;
        }
        else {  //顾客来了 窗口没空 需要等 
            que[i].startTime = minEndTime;
            que[i].waitTime = (minEndTime - que[i].arriveTime);
        }
        //更新窗口的结束时间 
        tables[poi] = que[i].startTime + que[i].serveTime;
        total += que[i].waitTime;
    }
	printf("%.1lf\n", total/60.0/que.size());
	return 0;
}
