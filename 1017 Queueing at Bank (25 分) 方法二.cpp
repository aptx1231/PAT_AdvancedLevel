#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//anyone comes too late (at or after 17:00:01) will not be served nor counted into the average.
//17:00:01�ŵ�����޷����ܷ��� ֻҪ��17:00:00��֮ǰ����Ķ��ܵõ����� 
//����˵�˿�һֱ�ȵ�17:00:00����û���յ����񣬾Ͳ�������

struct node {
    int arriveTime;
    int startTime;
    int serveTime;
    int waitTime;
    node(int ar = 0, int se = 0, int st = 0, int wt = 0) :
            arriveTime(ar), startTime(st), serveTime(se), waitTime(wt) {}
};

int tables[105];  //���ڽ���ʱ�� 

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
	//����ʱ���ʼ����8�� �ڴ�֮ǰ������� �͵õȴ� ��Ϊ�����������ʱ����8�� 
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
		if (arrivetime <= 17*60*60) {  //ֻ����17:00֮ǰ�����
			que.push_back(node(arrivetime, servicetime*60));
		} //que�������˶��÷����� 
	}
	sort(que.begin(), que.end(), com);
    long long total = 0;
    int cnt = 0;
	for (int i=0; i<que.size(); i++) {  //�������ǰ�˳���ÿ���˿ͷ�����������Ĵ��� 
        int minEndTime = 1<<30;
        int poi = 0;
        //����������ķ���̨
        for (int j=1;j<=k;j++) {
            if (tables[j] < minEndTime) {
                minEndTime = tables[j];
                poi = j;
            }
        }
        if (minEndTime < que[i].arriveTime) {  //�˿������� 
            que[i].startTime = que[i].arriveTime;
            que[i].waitTime = 0;
        }
        else {  //�˿����� ����û�� ��Ҫ�� 
            que[i].startTime = minEndTime;
            que[i].waitTime = (minEndTime - que[i].arriveTime);
        }
        //���´��ڵĽ���ʱ�� 
        tables[poi] = que[i].startTime + que[i].serveTime;
        total += que[i].waitTime;
    }
	printf("%.1lf\n", total/60.0/que.size());
	return 0;
}
