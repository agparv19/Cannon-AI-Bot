    #include<bits/stdc++.h>
    using namespace std;

double score(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax){

    int m = board.size();
    int n = board[0].size();

    if (isMax){
        int mt = 0; //mytownhalls
        int ot = 0; //opponent's townhalls

        for (int i=0; i<n; i++) if (board[0][i] == 'o') mt++;
        for (int i=0; i<n; i++) if (board[m-1][i] == 'x') ot++;

        double tms = 0; //tms is townhall margin score

        if (mt == 4 && ot == 2) tms = 10; 
        else if (mt == 3 && ot == 2) tms = 8; 
        else if (mt == 4 && ot == 3) tms = 7; 
        else if (mt == 4 && ot == 4) tms = 5; 
        else if (mt == 3 && ot == 3) tms = 5; 
        else if (mt == 3 && ot == 4) tms = 3; 
        else if (mt == 2 && ot == 3) tms = 2; 
        else if (mt == 2 && ot == 4) tms = 0; 

        double ams = positions[0].size(); //ams is army margin score
        ams = ams/100;

        return tms + ams;
    }
    else{

        int mt = 0; //mytownhalls
        int ot = 0; //opponent's townhalls

        for (int i=0; i<n; i++) if (board[m-1][i] == 'x') mt++;
        for (int i=0; i<n; i++) if (board[0][i] == 'o') ot++;

        double tms = 0; //tms is townhall margin score

        if (mt == 4 && ot == 2) tms = -10; 
        else if (mt == 3 && ot == 2) tms = -8; 
        else if (mt == 4 && ot == 3) tms = -7; 
        else if (mt == 4 && ot == 4) tms = -5; 
        else if (mt == 3 && ot == 3) tms = -5; 
        else if (mt == 3 && ot == 4) tms = -3; 
        else if (mt == 2 && ot == 3) tms = -2; 
        else if (mt == 2 && ot == 4) tms = 0; 

        double ams = positions[1].size(); //ams is army margin score
        ams = ams/100;

        return tms - ams;
    }

}

bool isEnemy(vector<vector<char>> &board, int r, int c, char opp){

    //returns true is opp is present at (r,c)
    int m = board.size();
    int n = board[0].size();

    if (r<0 || r>=m || c<0 || c>=n) return false;

    return board[r][c] == opp;
}

bool isEnemyAdjacent(vector<vector<char>> &board, bool isMax, int r, int c){

    if (isMax){
        char opp = 'b';
        char me = 'w';

        //check for enemy at r+1,c-1 ; r+1,c ; r+1,c+1 ; r,c-1 ; r,c+1
        if (isEnemy(board, r+1, c-1, opp)) return true;
        if (isEnemy(board, r+1, c, opp)) return true;
        if (isEnemy(board, r+1, c+1, opp)) return true;
        if (isEnemy(board, r, c-1, opp)) return true;
        if (isEnemy(board, r, c+1, opp)) return true;

        return false;
    }
    else{
        char opp = 'w';
        char me = 'b';

        //check for enemy at r-1,c-1 ; r-1,c ; r-1,c+1 ; r,c-1 ; r,c+1
        if (isEnemy(board, r-1, c-1, opp)) return true;
        if (isEnemy(board, r-1, c, opp)) return true;
        if (isEnemy(board, r-1, c+1, opp)) return true;
        if (isEnemy(board, r, c-1, opp)) return true;
        if (isEnemy(board, r, c+1, opp)) return true;

        return false;
    }
}

bool isOrthoCannon(vector<vector<char>> &board, int r, int c, bool isFront){

    int m = board.size();
    int n = board[0].size();

    int x = 1;

    if (!isFront) x = -1;

    int r1 = r+ x*1; 
    int r2 = r+ x*2;

    if (r1 <0 || r1>=m || r2<0 || r2>=m) return false;

    if (board[r1][c] == board[r][c] && board[r2][c] == board[r][c]) return true;

    return false;

}

bool isDiaCannon(vector<vector<char>> &board, int r, int c, bool isFront){

    //isFront is true when you want to check if this is a fron of a diagonal cannon

    int m = board.size();
    int n = board[0].size();

    int x = 1;

    if (!isFront) x = -1;

    int r1 = r+ x*1; 
    int r2 = r+ x*2;
    int c1 = c+ x*1;
    int c2 = c+ x*2;

    if (r1 <0 || r1>=m || r2<0 || r2>=m || c1 <0 || c1>=n || c2<0 || c2>=n) return false;

    if (board[r1][c1] == board[r][c] && board[r2][c2] == board[r][c]) return true;

    return false;
}

bool isValidForwardMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int r, int c, int rn, int cn){
    int m = board.size();
    int n = board[0].size();

    int idx = 1; int x =-1;

    if (isMax) {
        idx = 0;
        x =1;
    }

    char opp = 'w';
    char me = 'b';

    if (isMax){
        opp = 'b';
        me = 'w';
    }

    if (rn <0 || rn>=m || cn<0 || cn>=n) return false;

    if (positions[idx].find({r,c}) == positions[idx].end()) return false;

    if (board[rn][cn] != '.') return false;

    
    if (rn == r+ x*1 && (cn == c-1 || cn == c || cn == c+1)) return true;

    return false;
}

bool isValidCaptureMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int r, int c, int rn, int cn){
    int m = board.size();
    int n = board[0].size();

    int idx = 1; int x =-1;

    if (isMax) {
        idx = 0;
        x =1;
    }

    char opp = 'w';
    char me = 'b';
    char town = 'o';

    if (isMax){
        opp = 'b';
        me = 'w';
        town = 'x';
    }

    if (rn <0 || rn>=m || cn<0 || cn>=n) return false;

    if (positions[idx].find({r,c}) == positions[idx].end()) return false;

    if (board[rn][cn] != opp && board[rn][cn] != town) return false;

    if ((rn == r+ x*1 && (cn == c-1 || cn == c || cn == c+1)) || (rn == r && (cn == c-1 || cn == c+1))) return true;

    return false;
}

bool isValidRetreatMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int r, int c, int rn, int cn){
    int m = board.size();
    int n = board[0].size();

    int idx = 1; int x =-1;

    if (isMax) {
        idx = 0;
        x =1;
    }

    char opp = 'w';
    char me = 'b';
    char town = 'o';

    if (isMax){
        opp = 'b';
        me = 'w';
        town = 'x';
    }

    if (rn <0 || rn>=m || cn<0 || cn>=n) return false;

    if (positions[idx].find({r,c}) == positions[idx].end()) return false;

    if (!isEnemyAdjacent(board, isMax, r, c)) return false;

    if (board[rn][cn] == me) return false;

    if (rn == r-x*2 && (cn == c-2 || cn == c || cn == c+2)) return true;

    return false;
}

bool isValidCannonMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int r, int c, int rn, int cn){
    int m = board.size();
    int n = board[0].size();

    int idx = 1; int x =-1;

    if (isMax) {
        idx = 0;
        x =1;
    }

    char opp = 'w';
    char me = 'b';
    char town = 'o';

    if (isMax){
        opp = 'b';
        me = 'w';
        town = 'x';
    }

    if (rn <0 || rn>=m || cn<0 || cn>=n) return false;

    if (positions[idx].find({r,c}) == positions[idx].end()) return false;

    if (board[rn][cn] != '.') return false;

    if (isOrthoCannon(board, r, c, true)){
        if (rn == r+3 && cn == c) return true;
    }
    if (isOrthoCannon(board, r, c, false)){
        if (rn == r-3 && cn == c) return true;
    }

    if (isDiaCannon(board, r, c, true)){
        if (rn == r+3 && cn == c+3) return true;
    }
    if (isDiaCannon(board, r, c, false)){
        if (rn == r-3 && cn == c-3) return true;
    }

    return false;
}

bool isValidCannonShot(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int r, int c, int rn, int cn){
    int m = board.size();
    int n = board[0].size();

    int idx = 1; int x =-1;

    if (isMax) {
        idx = 0;
        x =1;
    }

    char opp = 'w';
    char me = 'b';
    char town = 'o';

    if (isMax){
        opp = 'b';
        me = 'w';
        town = 'x';
    }

    if (rn <0 || rn>=m || cn<0 || cn>=n) return false;

    if (positions[idx].find({r,c}) == positions[idx].end()) return false;

    if (board[rn][cn] == me) return false;

    if (town == 'x' && board[rn][cn] == 'o') return false;
    if (town == 'o' && board[rn][cn] == 'x') return false;

    if (isOrthoCannon(board, r, c, true)){
        if (r-1 >=0 && board[r-1][c] == '.' && cn == c && (rn == r-2 || rn == r-3)) return true;
    }
    if (isOrthoCannon(board, r, c, false)){
        if (r+1 <m && board[r+1][c] == '.' && cn == c && (rn == r+2 || rn == r+3)) return true;

    }

    if (isDiaCannon(board, r, c, true)){
        if (r-1 >=0 && c-1 >=0 && board[r-1][c-1] == '.' && (cn == c-2 || cn == c-3) && (rn == r-2 || rn == r-3)) return true;
    }
    if (isDiaCannon(board, r, c, false)){
        if (r+1 >=0 && c+1 >=0 && board[r+1][c+1] == '.' && (cn == c+2 || cn == c+3) && (rn == r+2 || rn == r+3)) return true;
    }

    return false;
}

pair<double, string> bestMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int depth, double alpha, double beta);

void forwardMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int depth, int r, int c, int rn, int cn, double &best, string &s, double alpha, double beta){

    int m = board.size();
    int n = board[0].size();

    int idx = 1;

    if (isMax) idx = 0;

    char opp = 'w';
    char me = 'b';

    if (isMax){
        opp = 'b';
        me = 'w';
    } 

    if (rn>=0 && rn<m && cn>=0 && cn<n && board[rn][cn] == '.'){
        board[r][c] = '.';
        board[rn][cn] = me;
        positions[idx].erase({r,c});
        positions[idx].insert({rn, cn});

        pair<double, string> temp = bestMove(board, positions, !isMax, depth+1, alpha, beta);

        if (isMax && temp.first > best){
            best = temp.first;
            s = "S " + to_string(r) + " " + to_string(c) + " " + "M " + to_string(rn) + " " + to_string(cn);
            //cout<<"best updated to: "<<best<<endl;
        }

        if (!isMax && temp.first < best){

            best = temp.first;
            s = "S " + to_string(r) + " " + to_string(c) + " " + "M " + to_string(rn) + " " + to_string(cn);
            //cout<<"best updated to: "<<best<<endl;
        }

        board[r][c] = me;
        board[rn][cn] = '.';
        positions[idx].erase({rn,cn});
        positions[idx].insert({r, c});

    }
}

void captureMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int depth, int r, int c, int rn, int cn, double &best, string &s, double alpha, double beta){

    int m = board.size();
    int n = board[0].size();

    int idx = 1;

    if (isMax) idx = 0;

    char town = 'o';
    char opp = 'w';
    char me = 'b';

    if (isMax){
        opp = 'b';
        me = 'w';
        town = 'x';
    } 

    

    if (rn>=0 && rn<m && cn>=0 && cn<n && (board[rn][cn] == opp || board[rn][cn] == town)){
        char og = board[rn][cn];
        board[r][c] = '.';
        board[rn][cn] = me;
        positions[idx].erase({r,c});
        positions[idx].insert({rn, cn});
        positions[idx^1].erase({rn, cn}); //remove the captured soldier from opponent's position collection
        

        pair<double, string> temp = bestMove(board, positions, !isMax, depth+1, alpha, beta);

        if (isMax && temp.first > best){
            best = temp.first;
            s = "S " + to_string(r) + " " + to_string(c) + " " + "M " + to_string(rn) + " " + to_string(cn);
        }

        if (!isMax && temp.first < best){
            best = temp.first;
            s = "S " + to_string(r) + " " + to_string(c) + " " + "M " + to_string(rn) + " " + to_string(cn);
        }

        board[r][c] = me;
        board[rn][cn] = og;
        positions[idx].erase({rn,cn});
        positions[idx].insert({r, c});
        if (og == opp) positions[idx^1].insert({rn, cn});
    }
}

void retreatMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int depth, int r, int c, int rn, int cn, double &best, string &s, double alpha, double beta){

    int m = board.size();
    int n = board[0].size();

    int idx = 1;

    if (isMax) idx = 0;

    char town = 'o';
    char opp = 'w';
    char me = 'b';

    if (isMax){
        opp = 'b';
        me = 'w';
        town = 'x';
    } 

    if (rn>=0 && rn<m && cn>=0 && cn<n && (board[rn][cn] == '.' || board[rn][cn] == opp ||board[rn][cn] == town)){

        char og = board[rn][cn];
        board[r][c] = '.';
        board[rn][cn] = me;
        positions[idx].erase({r,c});
        positions[idx].insert({rn, cn});
        if(og == opp) positions[idx^1].erase({rn, cn}); //remove the captured soldier from opponent's position collection
        

        pair<double, string> temp = bestMove(board, positions, !isMax, depth+1, alpha, beta);

        if (isMax && temp.first > best){
            best = temp.first;
            s = "S " + to_string(r) + " " + to_string(c) + " " + "M " + to_string(rn) + " " + to_string(cn);
        }

        if (!isMax && temp.first < best){
            best = temp.first;
            s = "S " + to_string(r) + " " + to_string(c) + " " + "M " + to_string(rn) + " " + to_string(cn);
        }

        board[r][c] = me;
        board[rn][cn] = og;
        positions[idx].erase({rn,cn});
        positions[idx].insert({r, c});
        if (og == opp) positions[idx^1].insert({rn, cn});
    }


}


void cannonShot(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int depth, int r, int c, int rn, int cn, double &best, string &s, double alpha, double beta){
    //r,c is point of firing
    //rn, cn is the aim

    int m = board.size();
    int n = board[0].size();

    int idx = 1;

    if (isMax) idx = 0;

    char town = 'o';
    char opp = 'w';
    char me = 'b';

    if (isMax){
        opp = 'b';
        me = 'w';
        town = 'x';
    } 

    if (rn<0 || rn>=m || cn<0 || cn>=n) return;

    if (board[rn][cn] == me) return;

    char og = board[rn][cn];

    if(og == opp) {
        positions[idx^1].erase({rn, cn});
        board[rn][cn] = '.';
    }
    else if (og == town){
        board[rn][cn] = '.';
    }

    pair<double, string> temp = bestMove(board, positions, !isMax, depth+1, alpha, beta);

    if (isMax && temp.first > best){
        best = temp.first;
        s = "S " + to_string(r) + " " + to_string(c) + " " + "B " + to_string(rn) + " " + to_string(cn);
    }

    if (!isMax && temp.first < best){
        best = temp.first;
        s = "S " + to_string(r) + " " + to_string(c) + " " + "B " + to_string(rn) + " " + to_string(cn);
    }

    if(og == opp) {
        positions[idx^1].insert({rn, cn});
        board[rn][cn] = opp;
    }
    else if (og == town){
        board[rn][cn] = town;
    }
    
}

void cannonMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int depth, int r, int c, int rn, int cn, double &best, string &s, double alpha, double beta){
    //r,c is the soldier about to move
    //rn, cn is its new position

    int m = board.size();
    int n = board[0].size();

    int idx = 1;

    if (isMax) idx = 0;

    char town = 'o';
    char opp = 'w';
    char me = 'b';

    if (isMax){
        opp = 'b';
        me = 'w';
        town = 'x';
    } 

    if (rn<0 || rn>=m || cn<0 || cn>=n) return;

    if (board[rn][cn] != '.') return;

    board[r][c] = '.';
    board[rn][cn] = me;
    positions[idx].erase({r,c});
    positions[idx].insert({rn, cn});

    pair<double, string> temp = bestMove(board, positions, !isMax, depth+1, alpha, beta);

    if (isMax && temp.first > best){
        best = temp.first;
        s = "S " + to_string(r) + " " + to_string(c) + " " + "M " + to_string(rn) + " " + to_string(cn);
    }

    if (!isMax && temp.first < best){
        best = temp.first;
        s = "S " + to_string(r) + " " + to_string(c) + " " + "M " + to_string(rn) + " " + to_string(cn);
    }

    board[r][c] = me;
    board[rn][cn] = '.';
    positions[idx].insert({r,c});
    positions[idx].erase({rn, cn});
    
}


pair<double, string> bestMove(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int depth, double alpha, double beta){

    //cout<<"depth is: "<<depth<<endl;

    if (depth == 4){
        double d = score(board, positions, !isMax);
        return {d, ""};
    }

    double d1 = score(board, positions, true);
    double d2 = score(board, positions, false);

    if (d1 >= 8 || d2 <= -8){

        if (isMax && d2 <= -8) return {d2, ""};

        return {d1, ""};

    }

    int m = board.size();
    int n = board[0].size();

    int idx = 1; int x = -1; double best = INT_MAX;

    if (isMax){
        idx = 0;
        x = 1;
        best = INT_MIN;
    } 

    string s = "";

    vector<pair<int, int>> soldiers;

    for(auto it = positions[idx].begin(); it!=positions[idx].end(); it++){
        soldiers.push_back({(*it).first, (*it).second});
        //cout<<"r = "<<(*it).first<<" , c = "<<(*it).second<<endl;
    }

    //for(auto it = positions[idx].begin(); it!=positions[idx].end(); it++){
    for(int i = 0; i<soldiers.size(); i++){    

        int r = soldiers[i].first;
        int c = soldiers[i].second;

        //cout<<"r = "<<r<<" , c = "<<c<<endl;

        //comments are written for maximizer
        //can move to a forward empty point: r+1,c-1 ; r+1,c ; r+1,c+1
        forwardMove(board, positions, isMax, depth, r, c, r+ x*1, c-1, best, s, alpha, beta);
        if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

        forwardMove(board, positions, isMax, depth, r, c, r+ x*1, c, best, s, alpha, beta);
        if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

        forwardMove(board, positions, isMax, depth, r, c, r+ x*1, c+1, best, s, alpha, beta);
        if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

        //can capture adjacent: r+1,c-1 ; r+1,c ; r+1,c+1 ; r,c-1 ; r,c+1
        captureMove(board, positions, isMax, depth, r, c, r+ x*1, c-1, best, s, alpha, beta);
        if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

        captureMove(board, positions, isMax, depth, r, c, r+ x*1, c, best, s, alpha, beta);
        if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

        captureMove(board, positions, isMax, depth, r, c, r+ x*1, c+1, best, s, alpha, beta);
        if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

        captureMove(board, positions, isMax, depth, r, c, r, c-1, best, s, alpha, beta);
        if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

        captureMove(board, positions, isMax, depth, r, c, r, c+1, best, s, alpha, beta);
        if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

        //can retreat if enemy is adjacent: r-2,c-2 ; r-2,c ; r-2,c+2
        if (isEnemyAdjacent(board, isMax, r, c)){
            retreatMove(board, positions, isMax, depth, r, c, r- x*2, c-2, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            retreatMove(board, positions, isMax, depth, r, c, r- x*2, c, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            retreatMove(board, positions, isMax, depth, r, c, r- x*2, c+2, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;
        }

        //can fire cannon if it is end point of the cannon
        if (isOrthoCannon(board, r, c, true)){
            if (r-1 >=0 && board[r-1][c] == '.')cannonShot(board, positions, isMax, depth, r, c, r-2, c, best, s, alpha, beta); 
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            if (r-1 >=0 && board[r-1][c] == '.')cannonShot(board, positions, isMax, depth, r, c, r-3, c, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            cannonMove(board, positions, isMax, depth, r, c, r+3, c, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;
        }

        if (isOrthoCannon(board, r, c, false)){
            if (r+1 <m && board[r+1][c] == '.')cannonShot(board, positions, isMax, depth, r, c, r+2, c, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            if (r+1 <m && board[r+1][c] == '.')cannonShot(board, positions, isMax, depth, r, c, r+3, c, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            cannonMove(board, positions, isMax, depth, r, c, r-3, c, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;
        }

        if (isDiaCannon(board, r, c, true)){
            if (r-1 >=0 && c-1 >=0 && board[r-1][c-1] == '.')cannonShot(board, positions, isMax, depth, r, c, r-2, c-2, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            if (r-1 >=0 && c-1 >=0 && board[r-1][c-1] == '.')cannonShot(board, positions, isMax, depth, r, c, r-3, c-3, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            cannonMove(board, positions, isMax, depth, r, c, r-3, c-3, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;
        }

        if (isDiaCannon(board, r, c, false)){
            if (r+1 <m && c+1 <n && board[r+1][c+1] == '.')cannonShot(board, positions, isMax, depth, r, c, r+2, c+2, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            if (r+1 <m && c+1 <n && board[r+1][c+1] == '.')cannonShot(board, positions, isMax, depth, r, c, r+3, c+3, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;

            cannonMove(board, positions, isMax, depth, r, c, r+3, c+3, best, s, alpha, beta);
            if (isMax) alpha = max(alpha, best); if (!isMax) beta = min(beta, best); if (beta <= alpha) break;
        }

        //cout<<s<<endl;

    }

    return {best, s};
    
}

int updateBoard(vector<vector<char>> &board, vector<set<pair<int, int>>> &positions, bool isMax, int r, int c, int rn, int cn, bool isMove){

    int m = board.size();
    int n = board[0].size();

    int idx = 1;

    if (isMax) idx = 0;

    char town = 'o';
    char opp = 'w';
    char me = 'b';

    if (isMax){
        opp = 'b';
        me = 'w';
        town = 'x';
    } 

    if (!isMove){
        //it is a shot
        if (isValidCannonShot(board, positions, isMax, r, c, rn, cn)){
            char og = board[rn][cn];
            board[rn][cn] = '.';
            if (og == opp) positions[idx^1].erase({rn,cn});

            double d1 = score(board, positions, true);
            double d2 = score(board, positions, false);

            if (isMax && d1 > 8){
                cout<<"Game Over! White Player (w) won the game.\n";
                return -1;
            }
            if (!isMax && d2 < -8){
                cout<<"Game Over! Black Player (b) won the game.\n";
                return -1;
            }

            return 0;
        }
        else{
            string lost = "Black Player (b)";
            if (isMax) lost = "White Player (w)";

            cout<<"Invalid Shot! "<<lost<<" hast lost the game.\n";

            return -1; //-1 will signify stop the game;
        }
    }

    if (isValidForwardMove(board, positions, isMax, r, c, rn, cn)){
        board[r][c] = '.';
        board[rn][cn] = me;
        positions[idx].erase({r,c});
        positions[idx].insert({rn,cn});
    }

    else if (isValidCaptureMove(board, positions, isMax, r, c, rn, cn)){

        char og = board[rn][cn];
        board[r][c] = '.';
        board[rn][cn] = me;
        positions[idx].erase({r,c});
        positions[idx].insert({rn,cn});
        if (og == opp) positions[idx^1].erase({rn,cn});
    }

    else if (isValidRetreatMove(board, positions, isMax, r, c, rn, cn)){

        char og = board[rn][cn];
        board[r][c] = '.';
        board[rn][cn] = me;
        positions[idx].erase({r,c});
        positions[idx].insert({rn,cn});
        if (og == opp) positions[idx^1].erase({rn,cn});
    }

    else if (isValidCannonMove(board, positions, isMax, r, c, rn, cn)){
        board[r][c] = '.';
        board[rn][cn] = me;
        positions[idx].erase({r,c});
        positions[idx].insert({rn,cn});
    }

    else{
        //Invalid move
        string lost = "Black Player (b)";
        if (isMax) lost = "White Player (w)";

        cout<<"Invalid Move! "<<lost<<" hast lost the game.\n";

        return -1; //-1 will signify stop the game;
    }

    double d1 = score(board, positions, true);
    double d2 = score(board, positions, false);


    if (isMax && d1 > 8){
        cout<<"Game Over! White Player (w) won the game.\n";
        return -1;
    }
    if (!isMax && d2 < -8){
        cout<<"Game Over! Black Player (b) won the game.\n";
        return -1;
    }

    return 0;
}

pair<bool, vector<int>> str2Move(string s){

    s = s.substr(2);

    vector<int> ans(4);

    string num = "";
    int i = 0;
    for (; i<s.size(); i++){
        if (s[i] == ' ') break;
        num += s[i];
    }

    ans[0] = stoi(num); //r


    i++;
    num = "";

    for (; i<s.size(); i++){
        if (s[i] == ' ') break;
        num += s[i];
    }

    ans[1] = stoi(num);

    i++;

    bool isMove = false;

    if (s[i] == 'M') isMove = true;

    i+=2;

    num = "";

    for (; i<s.size(); i++){
        if (s[i] == ' ') break;
        num += s[i];
    }

    ans[2] = stoi(num); //r

    i++;
    num = "";

    for (; i<s.size(); i++){
        num += s[i];
    }

    ans[3] = stoi(num);

    return {isMove, ans};

}





void printBoard(vector<vector<char>> &board){

    int m = board.size();
    int n = board[0].size();

    string space = "                                             ";
    cout<<space;
    cout<<"  ";
    for (int i=0; i<n; i++){
        cout<<i<<" ";
    }
    cout<<endl;

    for (int i=0; i<m; i++){
        cout<<space;
        cout<<i<<" ";
        for (int j=0; j<n; j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }

}

int main(){

    int m = 8;
    int n = 8;

    vector<vector<char>> board(m, vector<char>(n));

    //b - black player, w - white player , x- black townhall, o - white townhall

    if (m!=8 && n!=8){
        cout<<"Update the board first for new m and n\n";
        return 0;
    }

    board[0] = {'o','w','o','w','o','w','o','w'};
    board[1] = {'.','w','.','w','.','w','.','w'};
    board[2] = {'.','w','.','w','.','w','.','w'};
    board[3] = {'.','.','.','.','.','.','.','.'};
    board[4] = {'.','.','.','.','.','.','.','.'};
    board[5] = {'b','.','b','.','b','.','b','.'};
    board[6] = {'b','.','b','.','b','.','b','.'};
    board[7] = {'b','x','b','x','b','x','b','x'};

    cout<<"Welcome to The Game of Cannons!"<<endl;
    cout<<endl;
    printBoard(board);
    cout<<endl;

    vector<set<pair<int, int>>> positions(2, set<pair<int, int>>());

    //positions[0] represents positions of white player;
    //positions[1] represents positions of black player;

    positions[0].insert({0,1}); 
    positions[0].insert({0,3});
    positions[0].insert({0,5});
    positions[0].insert({0,7});
    positions[0].insert({1,1}); 
    positions[0].insert({1,3});
    positions[0].insert({1,5});
    positions[0].insert({1,7});
    positions[0].insert({2,1}); 
    positions[0].insert({2,3});
    positions[0].insert({2,5});
    positions[0].insert({2,7});

    positions[1].insert({5,0}); 
    positions[1].insert({5,2});
    positions[1].insert({5,4});
    positions[1].insert({5,6});
    positions[1].insert({6,0}); 
    positions[1].insert({6,2});
    positions[1].insert({6,4});
    positions[1].insert({6,6});
    positions[1].insert({7,0}); 
    positions[1].insert({7,2});
    positions[1].insert({7,4});
    positions[1].insert({7,6});

    bool gameNotOver = true;

    cout<<"You are player black ('b')"<<endl<<"Try to protect your townhalls (x) and attack bot's townhalls (o)\n";
    cout<<endl;
    cout<<"Do you want to play against the bot (press 1) or you want to watch bot play against itself (press 2)?\n";

    bool playingAgainstItself;
    string choice;
    getline(cin, choice);

    if (choice == "1"){
        playingAgainstItself = false;

        cout<<"To move a soldier from (R1, C1) to (R2, C2) type: "<<endl;
        cout<<"S R1 C1 M R2 C2"<<endl;

        cout<<endl;

        cout<<"To shoot at (R2, C2) using a soldier(part of cannon) located at (R1, C1) type: "<<endl;
        cout<<"S R1 C1 B R2 C2"<<endl;
        cout<<endl;

        cout<<"If the entered move is not in the correct format, game will throw an error and exit"<<endl;

        cout<<"If you are not sure of the rules yet, please visit: https://www.cse.iitd.ac.in/~mausam/courses/col333/autumn2019/A2/A2.pdf"<<endl;
        cout<<endl;

    } 
    else if (choice =="2"){
        playingAgainstItself = true;
    }
    else{
        cout<<"Invalid Choice. Existing!"<<endl;
        return 0;
    }

    //cout<<"Hit any key and Enter to start the game!"<<endl;
    //string enter = "";
    //cin>>enter;

    cout<<"The Game has started"<<endl;
    printBoard(board);
    cout<<endl;

    pair<bool, vector<int>> p;
    pair<double, string> b;

    while(gameNotOver){
        cout<<"Your turn: "<<endl;

        if (playingAgainstItself){
            b = bestMove(board, positions, false, 0, INT_MIN, INT_MAX);
            cout<<b.second<<endl;
        }
        else{
            
            string playerMove;
            getline(cin, playerMove);
            b.second = playerMove;
        }

        if (playingAgainstItself && b.second.size() == 0){
            double d1 = score(board, positions, true);
            double d2 = score(board, positions, false);

            if (d1 >= 7){
                cout<<"Game over! White Player (w) has won!"<<endl;
            }
            else if (d2 <= -7){
                cout<<"Game over! Black Player (b) has won!"<<endl;
            }
            else{
                cout<<"Game over! Match Draw!"<<endl;
            }
    
            break;
        }

        //p = str2Move(playerMove);
        p = str2Move(b.second);

        int player = updateBoard(board, positions, false, p.second[0], p.second[1], p.second[2], p.second[3], p.first);

        cout<<"Updated Board is: "<<endl;
        cout<<endl;

        printBoard(board);
        cout<<endl;


        if (player == -1) break;

        

        cout<<"Bot is making its move...."<<endl;

        b = bestMove(board, positions, true, 0, INT_MIN, INT_MAX);

        if (b.second.size() == 0){
            double d1 = score(board, positions, true);
            double d2 = score(board, positions, false);

            if (d1 >= 7){
                cout<<"Game over! White Player (w) has won!"<<endl;
            }
            else if (d2 <= -7){
                cout<<"Game over! Black Player (b) has won!"<<endl;
            }
            else{
                cout<<"Game over! Match Draw!"<<endl;
            }
    
            break;
        }
        cout<<b.second<<endl;
        p = str2Move(b.second);

        int bot = updateBoard(board, positions, true, p.second[0], p.second[1], p.second[2], p.second[3], p.first);

        cout<<"Updated Board is: "<<endl;
        cout<<endl;

        printBoard(board);
        cout<<endl;

        if (bot == -1) break;
    }




     


}
