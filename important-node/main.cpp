#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include<stdlib.h>
#include <ctime>
vector<int> d;//��¼�ڵ��


class A_Graph{
private:
    //V�ڵ���,E����
    int V;
    int E;
    vector<list<int>> adj;

public:
    A_Graph(int V,int E){
        this->V=V;
        this->E=E;
        adj.resize(V+1);
        d.resize(V+1,0);
    }
    int getV(){
        return V;
    };
    //�����
    void add(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
        d[u]++;
        d[v]++;
    }
    vector<int> adj_vector(int u){
        vector<int> v;
        for (const int &x : adj[u]) {
            v.push_back(x);
        }
        return v;
    }
    double f_average_d(){
        double sum=0;
        for(int i=0;i<d.size();i++){
            sum+=d[i];
        }
        double ave=sum/V;
        double f=1/ave;
        return f;
    }
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "�ڵ� " << i << " ���ڽӵ㣺";
            for (const int &x : adj[i]) {
                cout << x << " ";
            }
            cout<<"����Ϊ��"<<d[i]<<endl;
        }
    }

};

bool cmp_d(const int a,const int b){
    return d[a]>d[b];
}
vector<int> rankByD(A_Graph graph){
    int V=graph.getV();
    vector<int> nodes(V+1);
    for(int i=0;i<V;i++){
        nodes[i]=i;
    }
    sort(nodes.begin(),nodes.end(),cmp_d);
    return nodes;
}
struct Vote{
    int num;//���
    double score;//����=��
    bool v;//ͶƱ����
};

bool cmp_vote(Vote v1,Vote v2){
    return v1.score>v2.score;
}

vector<int> rankByVote(A_Graph graph,int k){
    vector<Vote> votes;
    vector<int> result;

    auto find_vote = [&votes](int idx) {
        for (int i = 0; i < votes.size(); i++) {
            if (votes[i].num == idx) {
                return i;  // ����ͶƱ��Ϣ������
            }
        }
        return -1;  // ���û�ҵ������� -1
    };

    for(int i=0;i<graph.getV();i++){
        votes.push_back({i,(double)d[i],1});
    }

    while(k--){
        sort(votes.begin(),votes.end(),cmp_vote);
        int nums;
        int flag=0;
        for(int i=0;i<votes.size();i++){
            if(votes[i].v){
                flag=1;
                nums=votes[i].num;
                break;
            }
        }

        if(flag==0){
            return result;
        }
        result.push_back(nums);
        votes[0]={nums,0,0};
        vector<int> adj=graph.adj_vector(nums);
        for(int i=0;i<adj.size();i++){
            int x=find_vote(i);
            votes[x].score=max(votes[x].score-graph.f_average_d(),0.0);//ԭ-f,0
        }

    }
    return result;
}

enum Status{
    S,I,R
};

int SIRmodel(A_Graph graph,vector<int> rankNode,double alpha){
    vector<Status> status(graph.getV()+1,S);
    queue<int> q;
    int Icnt=0;
    for(int node:rankNode){
        status[node]=I;
        q.push(node);
        Icnt++;
    }
    while(!q.empty()){
        int cNode=q.front();
        q.pop();
        status[cNode]=R;
        for(int neighbor:graph.adj_vector(cNode)){
            if(status[neighbor]==S) {
                double g=static_cast<double>(rand()) / RAND_MAX;
//                cout<<"1:"<<" "<<g<<endl;
                if (g < alpha) {
                    status[neighbor] = I;  // �ı�Ϊ��Ⱦ״̬
                    q.push(neighbor);      // ������У���������
                    Icnt++;       // ���¸�Ⱦ�ڵ���
                }
            }
        }
    }
    return Icnt;
}
//�涨�ڵ��0��ʼ
int main(){
    srand(static_cast<unsigned>(time(0)));
    ifstream infile("data/network.txt");
    if (!infile) {
        cerr << "Failed to open file" << endl;
        return 1;
    }
    int V,E;
    infile>>V>>E;
    A_Graph graph(V,E);
    int u, v;
    vector<pair<int, int>> edges;
    while (infile >> u >> v) {
        graph.add(u,v);
    }

    //graph.printGraph();

    cout<<"��������Ҫ�ڵ�����k";
    int k;
    cin>>k;
    clock_t start1 = clock();
    vector<int> rankNode_d= rankByD(graph);
    //cout<<"�ȵ�ѡ�����:"<<endl;

//    for(int i=0;i<k;i++){
//
//        cout<<"����±꣺"<<rankNode_d[i]<<" "<<"��Ӧ������С��"<<d[rankNode_d[i]]<<endl;
//    }
    clock_t end1 = clock();
    double duration1 = double(end1 - start1) / CLOCKS_PER_SEC;
    cout << "����D����ʱ��: " << duration1 << " ��" << endl;

    //!!!!!!rankNode_d��ʵ��ȫ���Ľڵ����sort֮��ģ�����Ҫ����ǰk��������ѡ���Ľڵ㣡��������������
    vector<int> rankNode_dk;
    for(int i=0;i<k;i++){
        rankNode_dk.push_back(rankNode_d[i]);
    }
    clock_t start2 = clock();
    vector<int> rankNode_vote= rankByVote(graph,k);
    //cout<<"ͶƱ��ѡ�����"<<endl;
//    for(int i=0;i<k;i++){
//        cout<<"����±꣺"<<rankNode_vote[i]<<" "<<"��Ӧ������С��"<<d[rankNode_vote[i]]<<endl;
//    }
    clock_t end2 = clock();
    double duration2 = double(end2 - start2) / CLOCKS_PER_SEC;
    cout << "����Vote����ʱ��: " << duration2 << " ��" << endl;


    double alpha=0.0;
    vector<double> DInfectionRate;
    vector<double> VoteInfectionRate;
    vector<double> alpharange;

    while(alpha<=1.0){
        alpharange.push_back(alpha);
        int infectedCount1=SIRmodel(graph,rankNode_dk,alpha);
        double I1= double(infectedCount1)/ double(graph.getV());
        //cout << "�ȵ�ѡ��������ո�Ⱦ�ı���: " << I1 << endl;
        DInfectionRate.push_back(I1);

        int infectedCount2=SIRmodel(graph,rankNode_vote,alpha);
        //cout<<infectedCount2<<" "<<graph.getV()<<endl;
        double I2=double(infectedCount2)/double(graph.getV());
        //cout << "ͶƱ��ѡ��������ո�Ⱦ�ı���: " << I2 << endl;
        VoteInfectionRate.push_back(I2);
        alpha+=0.05;
        cout<<"����..."<<endl;
    }

    FILE* dataFile = fopen("data1.txt", "w");
    if (dataFile == nullptr) {
        cerr << "Error opening data file!" << endl;
        return 1;
    }
    // д�����ݵ��ļ�
    for (size_t i = 0; i < alpharange.size(); i++) {
        fprintf(dataFile, "%f %f %f\n", alpharange[i], DInfectionRate[i],VoteInfectionRate[i]);
    }
    fclose(dataFile);

    return 0;
}
