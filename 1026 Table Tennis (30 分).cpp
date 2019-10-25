#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;

//If one cannot get a table before the closing time, their information must NOT be printed.
//��ֹʱ��ǰ�޷��õ�����ľͲ�������

struct node {
    int arriveTime;
    int startTime;
    int serveTime;
    int waitTime;
    int isVip;
    int tableId;
    node(int ar = 0, int se = 0, int iv = 0, int st = 0, int wt = 0, int ti = -1) :
            arriveTime(ar), startTime(st), serveTime(se), isVip(iv), tableId(ti), waitTime(wt) {}
};

struct table {
    int endTime;
    int vip;
    int num;
    //����ʱ��������8��
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
        if (serve > 120) {   //���2Сʱ ��120����  ��ʱ��Ҫѹ��ʱ��
            serve = 120;
        }
        que.push_back(node(trans(time), serve*60, isVip));
    }
    int m,k;
    cin >> k >> m;
    while (m--) {
        int tmp;
        cin >> tmp;
        tables[tmp].vip = 1;
    }
    sort(que.begin(), que.end(), com);
    for (int i=0;i<que.size();) {
        int minEndTime = 21*60*60;
        int poi = 0;
        //����������ķ���̨
        for (int j=1;j<=k;j++) {
            if (tables[j].endTime < minEndTime) {
                minEndTime = tables[j].endTime;
                poi = j;
            }
        }
        if (minEndTime == 21*60*60) {  //���з��������������ʱ�䶼����21�� ��ߵĹ˿;Ͳ��ܱ�������
            break;
        }
        if (tables[poi].vip) {  //�����������vip��
            //�ȿ���ǰʱ��minEndTime����������û��vip
            int flag = 1;
            for (int l=i; l < que.size() && que[l].arriveTime <= minEndTime; l++) {
                if (que[l].isVip && que[l].tableId == -1) {
                    que[l].tableId = poi;
                    if (minEndTime < que[l].arriveTime) {
                        que[l].startTime = que[l].arriveTime;
                        que[l].waitTime = 0;
                    }
                    else {
                        que[l].startTime = minEndTime;
                        que[l].waitTime = (minEndTime - que[l].arriveTime);
                    }
                    tables[poi].endTime = que[l].startTime + que[l].serveTime;
                    if (que[l].startTime < 21*60*60) {
                        tables[poi].num++;
                    }
                    flag = 0;  //�ҵ���vip ��ʱi����++
                    break;
                }
            }
            if (flag) {  //û���ҵ�vip ��ѡ���һ����
                que[i].tableId = poi;
                if (minEndTime < que[i].arriveTime) {
                    que[i].startTime = que[i].arriveTime;
                    que[i].waitTime = 0;
                }
                else {
                    que[i].startTime = minEndTime;
                    que[i].waitTime = (minEndTime - que[i].arriveTime);
                }
                tables[poi].endTime = que[i].startTime + que[i].serveTime;
                if (que[i].startTime < 21*60*60) {
                    tables[poi].num++;
                }
                i++;
            }
        }
        else {  //��������Ĳ���vip��
            if (que[i].isVip) {  //��һ������vip Ӧ������ѡ��vip�� ��ȥ�ҵ�ǰʱ��que[i].arriveTime��û��vip��
                if (que[i].tableId == -1) {  //û�б���������ӵ�vip ��Ϊvip������֮ǰ��vip������ʱ ֱ�ӱ�������
                    int vipTable = -1;
                    for (int j=1;j<=k;j++) {  //����ʱ��Ҫ�ڵ�ǰ�˵ĵ���ʱ��֮ǰ
                        if (tables[j].vip && tables[j].endTime <= que[i].arriveTime) {
                            vipTable = j;
                            break;
                        }
                    }
                    if (vipTable != -1) {  //�ҵ�vip����
                        que[i].tableId = vipTable;
                        poi = vipTable;  //Ϊ�˺�߿��Ժ���һ��д
                    }
                    else {  //û��vip��
                        que[i].tableId = poi;
                    }
                }
                else {  //������һ�����������vip ֱ��Խ��
                    i++;
                    continue;
                }
            }
            else {  //��һ����Ҳ����vip ֱ�ӷ���
                que[i].tableId = poi;
            }
            if (minEndTime < que[i].arriveTime) {
                que[i].startTime = que[i].arriveTime;
                que[i].waitTime = 0;
            }
            else {
                que[i].startTime = minEndTime;
                que[i].waitTime = (minEndTime - que[i].arriveTime);
            }
            tables[poi].endTime = que[i].startTime + que[i].serveTime;
            if (que[i].startTime < 21*60*60) {
                tables[poi].num++;
            }
            i++;
        }
    }
    sort(que.begin(), que.end(), com2);
    for (int i=0;i<que.size();i++) {
        //������8-21��֮�� 21��ǰû��ִ�е����˵�startTime�ǳ�ʼֵ0 �������
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
