#define HEAD_INFO
#include "sfmt/SFMT.h"
using namespace std;
typedef double (*pf)(int,int); 
class Graph
{
    public:
        int n, m, k;
        vector<int> inDeg;
        vector<vector<int>> gT;
        vector<vector<int>> originalGraph;

        vector<vector<double>> probT;


        vector<bool> visit;
        vector<int> visit_mark;
        enum InfluModel {IC, LT};
        InfluModel influModel;
        void setInfuModel(InfluModel p){
            influModel=p;
        }

        string folder;
        string graph_file;
        void readNM(){
            ifstream cin((folder+"attribute.txt").c_str());
            ASSERT(!cin == false);
            string s;
            while(cin >> s){
                if(s.substr(0,2)=="n="){
                    n=atoi(s.substr(2).c_str());
                    continue;
                }
                if(s.substr(0,2)=="m="){
                    m=atoi(s.substr(2).c_str());
                    continue;
                }
                ASSERT(false);
            }
            visit_mark=vector<int>(n);
            visit=vector<bool>(n);
            cin.close();
        }
        void add_edge(int a, int b, double p){
            probT[b].push_back(p);
            gT[b].push_back(a);
            originalGraph[a].push_back(b);
            inDeg[b]++;
        }
        vector<bool> hasnode;
        void readGraph(){
            FILE * fin= fopen((graph_file).c_str(), "r");

            cout << "\n Tryingn Reading file: " << graph_file;
            ASSERT(fin != false);
            int readCnt=0;
            cout << "\n Reading file: " << graph_file;
            for(int i=0; i<m; i++){
                readCnt ++;
                int a, b;
                double p = 0;
                int c=fscanf(fin, "%d%d", &a, &b);
                // ASSERT(c==3);
                // ASSERTT(c==3, a, b, p, c);
                ASSERT( a<n );
                ASSERT( b<n );
                hasnode[a]=true;
                hasnode[b]=true;
                add_edge(a, b, p);
            }
            cout << "Done reading edges";
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < gT[i].size(); j++)
                {
                    int v = i;
                    int u = gT[i][j];
                    probT[v][j] = (double)1/(double)inDeg[v];
                }
            }
            if(readCnt !=m)
                ExitMessage("m not equal to the number of edges in file "+graph_file);
            fclose(fin);
        }

        Graph(string folder, string graph_file):folder(folder), graph_file(graph_file){
            readNM();

            //init vector
            FOR(i, n){
                gT.push_back(vector<int>());
                originalGraph.push_back(vector<int>());
                hasnode.push_back(false);
                probT.push_back(vector<double>());
                //hyperGT.push_back(vector<int>());
                inDeg.push_back(0);
            }

            readGraph();
        }

};
double sqr(double t)
{
    return t*t;
}

#include "infgraph.h"
#include "timgraph.h"


