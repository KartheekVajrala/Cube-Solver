#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 1e9+7;

class Face{
    public:
        int side[3][3];
        int col;
        ll hash_val;
        Face(int _col){
            hash_val = 7;
            col = _col;
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    side[i][j] = _col;
        }

        void rotate(){
            swap(side[0][0],side[2][0]);
            swap(side[2][0],side[2][2]);
            swap(side[2][2],side[0][2]);
            swap(side[0][1],side[1][0]);
            swap(side[1][0],side[2][1]);
            swap(side[2][1],side[1][2]);
        }
        
        void rrotate(){
            rotate();rotate();rotate();
        }

        ll hash(){
            ll sum = 0;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    sum = sum*hash_val+(ll)side[i][j];
                }
            }
            return sum;
        }

        void print(){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++)
                    cout << side[i][j] << " ";
                cout << endl;
            }cout << endl;
        }

        bool solved(){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(side[i][j]!=side[1][1])return false;
                }
            }
            return true;
        }

        void swapt(Face* other){
            swap(side[0][0],other->side[0][0]);
            swap(side[0][1],other->side[0][1]);
            swap(side[0][2],other->side[0][2]);
        }
};

class Cube{
    public:
        Face* top;
        Face* bottom;
        Face* left;
        Face* right;
        Face* front;
        Face* back;
        ll hash_val;
        
        Cube(){
            top = new Face(1);
            bottom = new Face(2);
            left = new Face(3);
            right = new Face(4);
            front = new Face(5);
            back = new Face(6);
            hash_val = 11;
        }
        
        ~Cube(){
            delete top;
            delete bottom;
            delete right;
            delete left;
            delete front;
            delete back;
        }

        void rotate_top_side(){
            top_rotate();
        }

        void rev_rotate_top_side(){
            r_top_rotate();
        }

        void rotate_front_side(){
            vertical_front_flip();
            top_rotate();
            r_vertical_front_flip();
        }

        void rev_rotate_front_side(){
            vertical_front_flip();
            r_top_rotate();
            r_vertical_front_flip();
        }

        void rotate_left_side(){
            vertical_side_flip();
            top_rotate();
            r_vertical_side_flip();
        }

        void rev_rotate_left_side(){
            vertical_side_flip();
            r_top_rotate();
            r_vertical_side_flip();
        }

        void rotate_right_side(){
            r_vertical_side_flip();
            top_rotate();
            vertical_side_flip();
        }

        void rev_rotate_right_side(){
            r_vertical_side_flip();
            r_top_rotate();
            vertical_side_flip();
        }

        void rotate_back_side(){
            r_vertical_front_flip();
            top_rotate();
            vertical_front_flip();
        }

        void rev_rotate_back_side(){
            r_vertical_front_flip();
            r_top_rotate();
            vertical_front_flip();
        }

        void rotate_bottom_side(){
            vertical_front_flip();
            vertical_front_flip();
            top_rotate();
            vertical_front_flip();
            vertical_front_flip();
        }

        void rev_rotate_bottom_side(){
            vertical_front_flip();
            vertical_front_flip();
            r_top_rotate();
            vertical_front_flip();
            vertical_front_flip();
        }

        ll hash(){
            ll hash_sum = top->hash();
            hash_sum %= MOD;
            hash_sum = hash_sum*hash_val + bottom->hash();
            hash_sum %= MOD;
            hash_sum = hash_sum*hash_val + left->hash();
            hash_sum %= MOD;
            hash_sum = hash_sum*hash_val + right->hash();
            hash_sum %= MOD;
            hash_sum = hash_sum*hash_val + front->hash();
            hash_sum %= MOD;
            hash_sum = hash_sum*hash_val + back->hash();
            hash_sum %= MOD;
            return hash_sum;
        }

        bool solved(){
            return top->solved() && bottom->solved() && left->solved() && right->solved() && front->solved() && back->solved();
        }

        void print(){
            for(int i=0;i<3;i++){
                for(int j=0;j<6;j++){
                    if(j<3){
                        cout << "  ";
                    }else{
                        cout << top->side[i][j-3] << " ";
                    }
                }cout << endl;
            }
            for(int i=0;i<3;i++){
                for(int j=0;j<12;j++){
                    if(j<3)
                        cout << left->side[i][j] << " ";
                    else if(j<6)
                        cout << front->side[i][j-3] << " ";
                    else if(j<9)
                        cout << right->side[i][j-6] << " ";
                    else
                        cout << back->side[i][j-9] << " ";
                }cout << endl;
            }
            for(int i=0;i<3;i++){
                for(int j=0;j<6;j++){
                    if(j<3){
                        cout << "  ";
                    }else{
                        cout << bottom->side[i][j-3] << " ";
                    }
                }cout << endl;
            }
            for(int i=0;i<40;i++)cout << "#";cout << endl;
        }
    
    private:

        void top_rotate(){
            top->rotate();
            front->swapt(right);
            right->swapt(back);
            back->swapt(left);
        }

        void r_top_rotate(){
            top_rotate();top_rotate();top_rotate();
        }

        void horizontal_flip(){
            swap(front,left);
            swap(front,back);
            swap(front,right);
            top->rotate();
            bottom->rrotate();
        }

        void r_horizontal_flip(){
            horizontal_flip();horizontal_flip();horizontal_flip();
        }

        void vertical_side_flip(){
            swap(top,right);
            swap(top,bottom);
            swap(top,left);
            front->rotate();
            back->rrotate();
            top->rotate();
            bottom->rotate();
            right->rotate();
            left->rotate();
        }

        void r_vertical_side_flip(){
            vertical_side_flip();vertical_side_flip();vertical_side_flip();
        }

        void vertical_front_flip(){
            swap(front,top);
            swap(front,back);
            swap(front,bottom);
            right->rotate();
            left->rrotate();
            back->rotate();
            back->rotate();
            bottom->rotate();
            bottom->rotate();
        }

        void r_vertical_front_flip(){
            vertical_front_flip();vertical_front_flip();vertical_front_flip();
        }

};

int MAX_DEPTH = 8;
bool sol_found = false;
map<pair<ll,ll>,ll> mp;

void dfs(Cube &cube,string s,int depth){
    if(cube.solved()){
        cout << "SOLUTION FOUND" << endl;
        cout << "Solution : " << s << endl;
        cube.print();
        sol_found = true;
        return;
    }

    if(depth>MAX_DEPTH || sol_found)return;

    if(mp[{cube.hash(),depth}]>0){
        return;
    }

    // rotating top side
    cube.rotate_top_side();
    dfs(cube,s+'T',depth+1);
    cube.rev_rotate_top_side();

    // rotating front side
    cube.rotate_front_side();
    dfs(cube,s+'F',depth+1);
    cube.rev_rotate_front_side();

    // rotating left side
    cube.rotate_left_side();
    dfs(cube,s+'L',depth+1);
    cube.rev_rotate_left_side();

    // rotating right side
    cube.rotate_right_side();
    dfs(cube,s+'R',depth+1);
    cube.rev_rotate_right_side();

    // rotating back side
    cube.rotate_back_side();
    dfs(cube,s+'B',depth+1);
    cube.rev_rotate_back_side();

    //rotating bottom side
    cube.rotate_bottom_side();
    dfs(cube,s+'D',depth+1);
    cube.rev_rotate_bottom_side();

    mp[{cube.hash(),depth}] = 1;
}

int main(){
    Cube cube;
    cout << cube.solved() << endl;
    cube.rev_rotate_top_side();
    cube.rev_rotate_top_side();
    cube.rotate_front_side();
    cube.rev_rotate_right_side();
    cout << cube.solved() << endl;

    cube.print();
    cout << "START SOLVING ..." << endl;
    clock_t start = clock();
    dfs(cube,"",0);
    clock_t end = clock();

    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    cout << "FINISHED" << endl;
    printf("Time measured: %.3f seconds.\n", elapsed);
}