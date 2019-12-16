#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <ctime>
#include <set>

using namespace std;
class puyo{
    public:
	typedef pair<int, int> point;
	map<point, int> m;
	vector<point> movable_vec;
	int cur_type;
	int score;
	set<point> p_set;

	puyo(){
	    for(int i = 0; i<5;i++){
		for(int j =0; j < 12; j++){
		    m.insert(make_pair(make_pair(i,j), 0));
		}
	    }
	    cur_type = 0;
	    score = 0;
	}

	void set_insert(point p){
	    if(p_set.count(p) == 0){
		p_set.insert(p);
		if(p.first > 0){
		    point left_p = make_pair(p.first-1,p.second);
		    if(m.find(left_p)->second == m.find(p)->second){
			set_insert(left_p);
		    }
		}
		if(p.first < 4){
		    point right_p = make_pair(p.first+1,p.second);
		    if(m.find(right_p)->second == m.find(p)->second){
			set_insert(right_p);
		    }
		}
		if(p.second > 0){
		    point bottom_p = make_pair(p.first,p.second-1);
		    if(m.find(bottom_p)->second == m.find(p)->second){
			set_insert(bottom_p);
		    }
		}
		if(p.second < 11){
		    point top_p = make_pair(p.first,p.second+1);
		    if(m.find(top_p)->second == m.find(p)->second){
			set_insert(top_p);
		    }
		}
	    } else {
		return;
	    }
	    
	}


	bool explosion(){
	    /*
	     모든 좌표를 탐색한다
	     탐색할때
	     좌표와 연결되는 좌표를 셋에 집어넣는다
	     연결되는 좌표와 연결되는 좌표를 셋에집어넣는다 이때 이미 연결한 좌표는 집어넣지않는다
	     더이상 연결이 안되면 셋의 크기를 반환한다
	     셋이 4 이상이면 셋에 들어있는  모든 좌표의 컬러를 0으로 만든다
	     */
	    int exp_count = 0;
	    for(int y=0;y <12; y++){
		for(int x=0;x<5;x++){
		    point p = make_pair(x,y);
		    int p_color = m.find(p)->second;
		    if(p_color != 0){
			set_insert(p);
			if(p_set.size() >= 4){
			    for(auto it = p_set.begin(); it != p_set.end(); it++){
				point it_p = *it;
				int px = it_p.first;
				int py = it_p.second;
				point exp_p = make_pair(px, py);
				m.find(exp_p)->second = 0;
				exp_count++;
			    }
			}
		    }
		    p_set.clear();
		}
	    }

	    if(exp_count != 0){
		score++;
		return true;
	    } else {
		return false;
	    }

	}


	bool can_left(){
	    /*
	       1.현재좌표를 모두 탐색
	       2-0.현재 모든 좌표중 하나라도  x좌표가 0 이면 false
	       2-1.현재 좌표의 모든 왼쪽 중 두개 비어잇어야 함
	       2-2.현재좌표의 모든왼쪽 3개 (세로모양) 왼쪽하나만 1개(가로모양)
	       2-3.현재 모든 좌표의 왼쪽 중 세개
	       */
	    if(cur_type == 1){
		int empty_slots = 0;
		for(int i = 0; i < 3; i++){
		    if(movable_vec[i].first == 0){
			return false;
		    }
		    point left_p = make_pair(movable_vec[i].first-1,movable_vec[i].second);
		    if(m.find(left_p)->second == 0){
			empty_slots++;
		    }
		}

		if(empty_slots == 2){
		    return true;
		}

		return false;
	    }

	    if(cur_type == 2){
		int empty_slots = 0;
		bool is_stick = false;
		if(movable_vec[0].first == movable_vec[1].first){
		    is_stick = true;
		}
		for(int i =0;i<3;i++){
		    if(movable_vec[i].first == 0){
			return false;
		    }
		    point left_p = make_pair(movable_vec[i].first-1,movable_vec[i].second);
		    if(m.find(left_p)->second == 0){
			empty_slots++;
		    }
		}
		if(is_stick){
		    if(empty_slots == 3){
			return true;
		    }
		} else {
		    if(empty_slots == 1){
			return true;
		    }
		}
		return false;
	    }

	    if(cur_type == 3){
		int empty_slots = 0;
		for(int i = 0; i < 5; i++){
		    if(movable_vec[i].first == 0){
			return false;
		    }
		    point left_p = make_pair(movable_vec[i].first-1, movable_vec[i].second);
		    if(m.find(left_p)->second == 0){
			empty_slots++;
		    }
		}

		if(empty_slots == 3){
		    return true;
		}
		return false;
	    }
	}

	void left(){
	    if(cur_type == 1 || cur_type == 2){
		point p1 = movable_vec[0];
		point p2 = movable_vec[1];
		point p3 = movable_vec[2];
		int color_1 = m.find(p1)->second;
		int color_2 = m.find(p2)->second;
		int color_3 = m.find(p3)->second;
		
		m.find(p1)->second = 0;
		m.find(p2)->second = 0;
		m.find(p3)->second = 0;

		point new_p1 = make_pair(p1.first-1,p1.second);
		point new_p2 = make_pair(p2.first-1,p2.second);
		point new_p3 = make_pair(p3.first-1,p3.second);
		
		m.find(new_p1)->second = color_1;
		m.find(new_p2)->second = color_2;
		m.find(new_p3)->second = color_3;

		while(!movable_vec.empty()){
		    movable_vec.pop_back();
		}
		movable_vec.push_back(new_p1);
		movable_vec.push_back(new_p2);
		movable_vec.push_back(new_p3);
	    }
	    if(cur_type == 3){
		point p1 = movable_vec[0];
		point p2 = movable_vec[1];
		point p3 = movable_vec[2];
		point p4 = movable_vec[3];
		point p5 = movable_vec[4];

		int color_1 = m.find(p1)->second;
		int color_2 = m.find(p2)->second;
		int color_3 = m.find(p3)->second;
		int color_4 = m.find(p4)->second;
		int color_5 = m.find(p5)->second;
		
		m.find(p1)->second = 0;
		m.find(p2)->second = 0;
		m.find(p3)->second = 0;
		m.find(p4)->second = 0;
		m.find(p5)->second = 0;

		point new_p1 = make_pair(p1.first-1,p1.second);
		point new_p2 = make_pair(p2.first-1,p2.second);
		point new_p3 = make_pair(p3.first-1,p3.second);
		point new_p4 = make_pair(p4.first-1,p4.second);
		point new_p5 = make_pair(p5.first-1,p5.second);
		
		m.find(new_p1)->second = color_1;
		m.find(new_p2)->second = color_2;
		m.find(new_p3)->second = color_3;
		m.find(new_p4)->second = color_4;
		m.find(new_p5)->second = color_5;

		while(!movable_vec.empty()){
		    movable_vec.pop_back();
		}
		movable_vec.push_back(new_p1);
		movable_vec.push_back(new_p2);
		movable_vec.push_back(new_p3);
		movable_vec.push_back(new_p4);
		movable_vec.push_back(new_p5);
	    }
	}

	bool can_right(){
	     
	    if(cur_type == 1){
		int empty_slots = 0;
		for(int i = 0; i < 3; i++){
		    if(movable_vec[i].first == 4){
			return false;
		    }
		    point right_p = make_pair(movable_vec[i].first+1,movable_vec[i].second);
		    if(m.find(right_p)->second == 0){
			empty_slots++;
		    }
		}

		if(empty_slots == 2){
		    return true;
		}

		return false;
	    }

	    if(cur_type == 2){
		int empty_slots = 0;
		bool is_stick = false;
		if(movable_vec[0].first == movable_vec[1].first){
		    is_stick = true;
		}
		for(int i =0;i<3;i++){
		    if(movable_vec[i].first == 4){
			return false;
		    }
		    point right_p = make_pair(movable_vec[i].first+1,movable_vec[i].second);
		    if(m.find(right_p)->second == 0){
			empty_slots++;
		    }
		}
		if(is_stick){
		    if(empty_slots == 3){
			return true;
		    }
		} else {
		    if(empty_slots == 1){
			return true;
		    }
		}
		return false;
	    }

	    if(cur_type == 3){
		int empty_slots = 0;
		for(int i = 0; i < 5; i++){
		    if(movable_vec[i].first == 4){
			return false;
		    }
		    point right_p = make_pair(movable_vec[i].first+1, movable_vec[i].second);
		    if(m.find(right_p)->second == 0){
			empty_slots++;
		    }
		}

		if(empty_slots == 3){
		    return true;
		}
		return false;
	    }
	}

	void right(){
	    if(cur_type == 1 || cur_type == 2){
		point p1 = movable_vec[0];
		point p2 = movable_vec[1];
		point p3 = movable_vec[2];
		int color_1 = m.find(p1)->second;
		int color_2 = m.find(p2)->second;
		int color_3 = m.find(p3)->second;
		
		m.find(p1)->second = 0;
		m.find(p2)->second = 0;
		m.find(p3)->second = 0;

		point new_p1 = make_pair(p1.first+1,p1.second);
		point new_p2 = make_pair(p2.first+1,p2.second);
		point new_p3 = make_pair(p3.first+1,p3.second);
		
		m.find(new_p1)->second = color_1;
		m.find(new_p2)->second = color_2;
		m.find(new_p3)->second = color_3;

		while(!movable_vec.empty()){
		    movable_vec.pop_back();
		}
		movable_vec.push_back(new_p1);
		movable_vec.push_back(new_p2);
		movable_vec.push_back(new_p3);
	    }
	    if(cur_type == 3){
		point p1 = movable_vec[0];
		point p2 = movable_vec[1];
		point p3 = movable_vec[2];
		point p4 = movable_vec[3];
		point p5 = movable_vec[4];

		int color_1 = m.find(p1)->second;
		int color_2 = m.find(p2)->second;
		int color_3 = m.find(p3)->second;
		int color_4 = m.find(p4)->second;
		int color_5 = m.find(p5)->second;
		
		m.find(p1)->second = 0;
		m.find(p2)->second = 0;
		m.find(p3)->second = 0;
		m.find(p4)->second = 0;
		m.find(p5)->second = 0;

		point new_p1 = make_pair(p1.first+1,p1.second);
		point new_p2 = make_pair(p2.first+1,p2.second);
		point new_p3 = make_pair(p3.first+1,p3.second);
		point new_p4 = make_pair(p4.first+1,p4.second);
		point new_p5 = make_pair(p5.first+1,p5.second);
		
		m.find(new_p1)->second = color_1;
		m.find(new_p2)->second = color_2;
		m.find(new_p3)->second = color_3;
		m.find(new_p4)->second = color_4;
		m.find(new_p5)->second = color_5;

		while(!movable_vec.empty()){
		    movable_vec.pop_back();
		}
		movable_vec.push_back(new_p1);
		movable_vec.push_back(new_p2);
		movable_vec.push_back(new_p3);
		movable_vec.push_back(new_p4);
		movable_vec.push_back(new_p5);
	    }


	}

	bool can_rotate(){
	    //type : 2일때 세로면 가로로돌았을때만 생각 아래의 y 좌표의 좌우x
	    if(cur_type == 2){
		bool is_stick = false;
		if(movable_vec[0].first == movable_vec[1].first){
		    is_stick = true;
		}
		if(is_stick){
		    if(movable_vec[0].first == 0 || movable_vec[0].first == 4){
			return false;
		    }
		    int min_y = movable_vec[0].second;
		    point bottom_p;
		    for(int i=0; i<3;i++){
			if(movable_vec[i].second < min_y){
			    min_y = movable_vec[i].second;
			    bottom_p = movable_vec[i];
			}
		    }

		    point left_p = make_pair(bottom_p.first-1,bottom_p.second+1);
		    point right_p = make_pair(bottom_p.first+1,bottom_p.second+1);

		    if(m.find(left_p)->second != 0){
			return false;
		    }
		    if(m.find(right_p)->second != 0){
			return false;
		    }
		    
		}
	    }
	    return true;
	}

	void rotate(){
	    /* 컬러만 고침
	       type 1 min_x, min_y, max_x, max_y 를 얻는다
	       type 2 세로일때(위 -> 오른쪽)(밑->왼쪽) 가로일때(왼쪽->위)(오른쪽->밑)
	       		중간의 좌표를 얻어서 구함
	       type3 movable_vec[]의 color 값들만 빼와서 컬러들만 고침
	       
	       type 1, 2 일때 movable_vec 갱신 
	     */
	    if(cur_type == 1){
		int min_x = movable_vec[0].first;
		int min_y = movable_vec[0].second;
		int max_x = movable_vec[0].first;
		int max_y = movable_vec[0].second;

		for(int i = 0; i < 3;i++){
		    if(movable_vec[i].first < min_x){
			min_x = movable_vec[i].first;
		    }
		    if(movable_vec[i].first > max_x){
			max_x = movable_vec[i].first;
		    }
		    if(movable_vec[i].second < min_y){
			min_y = movable_vec[i].second;
		    }
		    if(movable_vec[i].second > max_y){
			max_y = movable_vec[i].second;
		    }
		}

		point left_bottom_p = make_pair(min_x,min_y);
		point left_top_p = make_pair(min_x,max_y);
		point right_bottom_p = make_pair(max_x,min_y);
		point right_top_p = make_pair(max_x, max_y);

		if(m.find(left_bottom_p)->second == 0){
		    m.find(left_bottom_p)->second = m.find(right_bottom_p)->second;
		    m.find(right_bottom_p)->second = m.find(right_top_p)->second;
		    m.find(right_top_p)->second = m.find(left_top_p)->second;
		    m.find(left_top_p)->second = 0;

		    while(!movable_vec.empty()){
			movable_vec.pop_back();
		    }
		    movable_vec.push_back(left_bottom_p);
		    movable_vec.push_back(right_bottom_p);
		    movable_vec.push_back(right_top_p);
		}
		else if(m.find(left_top_p)->second == 0){
		    m.find(left_top_p)->second = m.find(left_bottom_p)->second;
		    m.find(left_bottom_p)->second = m.find(right_bottom_p)->second;
		    m.find(right_bottom_p)->second = m.find(right_top_p)->second;
		    m.find(right_top_p)->second = 0;

		    while(!movable_vec.empty()){
			movable_vec.pop_back();
		    }
		    movable_vec.push_back(left_bottom_p);
		    movable_vec.push_back(right_bottom_p);
		    movable_vec.push_back(left_top_p);


		}
		else if(m.find(right_top_p)->second == 0){
		    m.find(right_top_p)->second = m.find(left_top_p)->second;
		    m.find(left_top_p)->second = m.find(left_bottom_p)->second;
		    m.find(left_bottom_p)->second = m.find(right_bottom_p)->second;
		    m.find(right_bottom_p)->second = 0;

		    while(!movable_vec.empty()){
			movable_vec.pop_back();
		    }
		    movable_vec.push_back(left_bottom_p);
		    movable_vec.push_back(right_top_p);
		    movable_vec.push_back(left_top_p);
		}
		else if(m.find(right_bottom_p)->second == 0){
		    m.find(right_bottom_p)->second = m.find(right_top_p)->second;
		    m.find(right_top_p)->second = m.find(left_top_p)->second;
		    m.find(left_top_p)->second = m.find(left_bottom_p)->second;
		    m.find(left_bottom_p)->second = 0;

		    while(!movable_vec.empty()){
			movable_vec.pop_back();
		    }
		    movable_vec.push_back(right_bottom_p);
		    movable_vec.push_back(right_top_p);
		    movable_vec.push_back(left_top_p);
		}

	    }
	    if(cur_type == 2){
		bool is_stick = false;

		if(movable_vec[0].first == movable_vec[1].first){
		    is_stick = true;
		}

		if(is_stick){
		    int max_y = movable_vec[0].second;
		    int min_y = movable_vec[0].second;

		    for(int i =0; i < 3; i++){
			if(movable_vec[i].second < min_y){
			    min_y = movable_vec[i].second;
			}
			if(movable_vec[i].second > max_y){
			    max_y = movable_vec[i].second;
			}
		    }

		    point top_p;
		    point bottom_p;

		    for(int i =0; i<3;i++){
			if(movable_vec[i].second == max_y){
			    top_p = movable_vec[i];
			}
			if(movable_vec[i].second == min_y){
			    bottom_p = movable_vec[i];
			}
		    }

		    point right_p = make_pair(top_p.first+1, top_p.second-1);
		    point left_p = make_pair(top_p.first-1, top_p.second-1);

		    m.find(right_p)->second = m.find(top_p)->second;
		    m.find(left_p)->second = m.find(bottom_p)->second;
		    m.find(top_p)->second = 0;
		    m.find(bottom_p)->second = 0;

		    while(!movable_vec.empty()){
			movable_vec.pop_back();
		    }

		    point center_p = make_pair(top_p.first, top_p.second-1);

		    movable_vec.push_back(left_p);
		    movable_vec.push_back(center_p);
		    movable_vec.push_back(right_p);

		} else {
		    int max_x = movable_vec[0].first;
		    int min_x = movable_vec[0].first;

		    for(int i =0; i < 3; i++){
			if(movable_vec[i].first < min_x){
			    min_x = movable_vec[i].first;
			}
			if(movable_vec[i].first > max_x){
			    max_x = movable_vec[i].first;
			}
		    }

		    point left_p;
		    point right_p;

		    for(int i =0; i<3;i++){
			if(movable_vec[i].first == min_x){
			    left_p = movable_vec[i];
			}
			if(movable_vec[i].first == max_x){
			    right_p = movable_vec[i];
			}
		    }

		    point top_p = make_pair(left_p.first+1, left_p.second+1);
		    point bottom_p = make_pair(left_p.first+1, left_p.second-1);

		    m.find(top_p)->second = m.find(left_p)->second;
		    m.find(bottom_p)->second = m.find(right_p)->second;
		    m.find(left_p)->second = 0;
		    m.find(right_p)->second = 0;

		    while(!movable_vec.empty()){
			movable_vec.pop_back();
		    }

		    point center_p = make_pair(top_p.first, top_p.second-1);

		    movable_vec.push_back(top_p);
		    movable_vec.push_back(center_p);
		    movable_vec.push_back(bottom_p);


		}

	    }
	    if(cur_type == 3){
		int min_x = movable_vec[0].first;
		int min_y = movable_vec[0].second;
		int max_x = movable_vec[0].first;
		int max_y = movable_vec[0].second;

		for(int i = 0; i < 5;i++){
		    if(movable_vec[i].first < min_x){
			min_x = movable_vec[i].first;
		    }
		    if(movable_vec[i].first > max_x){
			max_x = movable_vec[i].first;
		    }
		    if(movable_vec[i].second < min_y){
			min_y = movable_vec[i].second;
		    }
		    if(movable_vec[i].second > max_y){
			max_y = movable_vec[i].second;
		    }
		}

		point top_p = make_pair((min_x+max_x)/2, max_y);
		point bottom_p = make_pair((min_x+max_x)/2, min_y);
		point left_p = make_pair(min_x,(min_y+max_y)/2);
		point right_p = make_pair(max_x, (min_y+max_y)/2);

		int top_color = m.find(top_p)->second;
		m.find(top_p)->second = m.find(left_p)->second;
		m.find(left_p)->second = m.find(bottom_p)->second;
		m.find(bottom_p)->second = m.find(right_p)->second;
		m.find(right_p)->second = top_color;
	    }
	    cout <<"rotate"<<endl;
	}

	void down_all(){
	    while(can_down()){
		down();
	    }
	}

	void down(){
	    /*
	       1.기존에있는 좌표와 color를  모두 저장
	       2.기존에있던곳의 좌표의 color를 모두 0으로
	       3.기존에있는 좌표의 -1 부분에 모두 color
	       4.movable_vec 업데이트;
	       */
	    if(cur_type == 1){
		point p1 = movable_vec[0];
		point p2 = movable_vec[1];
		point p3 = movable_vec[2];
		int color_1 = m.find(p1)->second;
		int color_2 = m.find(p2)->second;
		int color_3 = m.find(p3)->second;
		
		m.find(p1)->second = 0;
		m.find(p2)->second = 0;
		m.find(p3)->second = 0;

		point new_p1 = make_pair(p1.first,p1.second-1);
		point new_p2 = make_pair(p2.first,p2.second-1);
		point new_p3 = make_pair(p3.first,p3.second-1);
		
		m.find(new_p1)->second = color_1;
		m.find(new_p2)->second = color_2;
		m.find(new_p3)->second = color_3;

		while(!movable_vec.empty()){
		    movable_vec.pop_back();
		}
		movable_vec.push_back(new_p1);
		movable_vec.push_back(new_p2);
		movable_vec.push_back(new_p3);
	    }
	    if(cur_type == 2){
		point p1 = movable_vec[0];
		point p2 = movable_vec[1];
		point p3 = movable_vec[2];
		int color_1 = m.find(p1)->second;
		int color_2 = m.find(p2)->second;
		int color_3 = m.find(p3)->second;
		
		m.find(p1)->second = 0;
		m.find(p2)->second = 0;
		m.find(p3)->second = 0;

		point new_p1 = make_pair(p1.first,p1.second-1);
		point new_p2 = make_pair(p2.first,p2.second-1);
		point new_p3 = make_pair(p3.first,p3.second-1);
		
		m.find(new_p1)->second = color_1;
		m.find(new_p2)->second = color_2;
		m.find(new_p3)->second = color_3;

		while(!movable_vec.empty()){
		    movable_vec.pop_back();
		}
		movable_vec.push_back(new_p1);
		movable_vec.push_back(new_p2);
		movable_vec.push_back(new_p3);
	    }
	    if(cur_type == 3){
		point p1 = movable_vec[0];
		point p2 = movable_vec[1];
		point p3 = movable_vec[2];
		point p4 = movable_vec[3];
		point p5 = movable_vec[4];

		int color_1 = m.find(p1)->second;
		int color_2 = m.find(p2)->second;
		int color_3 = m.find(p3)->second;
		int color_4 = m.find(p4)->second;
		int color_5 = m.find(p5)->second;
		
		m.find(p1)->second = 0;
		m.find(p2)->second = 0;
		m.find(p3)->second = 0;
		m.find(p4)->second = 0;
		m.find(p5)->second = 0;

		point new_p1 = make_pair(p1.first,p1.second-1);
		point new_p2 = make_pair(p2.first,p2.second-1);
		point new_p3 = make_pair(p3.first,p3.second-1);
		point new_p4 = make_pair(p4.first,p4.second-1);
		point new_p5 = make_pair(p5.first,p5.second-1);
		
		m.find(new_p1)->second = color_1;
		m.find(new_p2)->second = color_2;
		m.find(new_p3)->second = color_3;
		m.find(new_p4)->second = color_4;
		m.find(new_p5)->second = color_5;

		while(!movable_vec.empty()){
		    movable_vec.pop_back();
		}
		movable_vec.push_back(new_p1);
		movable_vec.push_back(new_p2);
		movable_vec.push_back(new_p3);
		movable_vec.push_back(new_p4);
		movable_vec.push_back(new_p5);
	    }
	}


	bool can_down(){
	    if(cur_type == 1){
		int empty_slots = 0;

		for(int i=0; i< 3; i++){
		    point p = movable_vec[i];
		    point down_p = make_pair(p.first, p.second-1);
		    if(m.find(down_p)->second == 0){
			empty_slots++;
		    }
		}

		if(empty_slots == 2){
		    return true;
		}
		return false;
	    }

	    if(cur_type == 2){
		bool is_stick = true;
		if(movable_vec[0].first == movable_vec[1].first){
		    is_stick = true;
		} else {
		    is_stick = false;
		}

		int min_y = movable_vec[0].second;
		if(is_stick){
		    point min_y_point;

		    for(int i = 0; i < 3; i++){
			if(movable_vec[i].second < min_y){
			    min_y = movable_vec[i].second;
			    min_y_point = movable_vec[i];
			}
		    }

		    if(min_y == 0){
			return false;
		    }
		    
		    point down_point = make_pair(min_y_point.first, min_y_point.second-1);
		    if(m.find(down_point)->second != 0){
			return false;
		    }
		} else {

		    if(min_y == 0){
			return false;
		    }
		    point down_point;
		    for(int j = 0; j < 3; j++){
			down_point = make_pair(movable_vec[j].first, movable_vec[j].second-1);
			if(m.find(down_point)->second != 0){
			    return false;
			}
		    }
		}

		return true;

	    }

	    if(cur_type == 3){
		point min_yp;
		point left_xp;
		point right_xp;

		min_yp = movable_vec[0];
		left_xp = movable_vec[0];
		right_xp = movable_vec[0];
		
		//find min_yp
		for(int i = 0; i < 5; i++){
		   if(min_yp.second > movable_vec[i].second){
		       min_yp = movable_vec[i];
		   }
		}

		//find left_xp
		for(int i = 0; i <5; i++){
		    if(movable_vec[i].second == min_yp.second+1){
			if(movable_vec[i].first < min_yp.first){
			    left_xp = movable_vec[i];
			}
		    }
		}
		for(int i = 0; i <5; i++){
		    if(movable_vec[i].second == min_yp.second+1){
			if(movable_vec[i].first > min_yp.first){
			    right_xp = movable_vec[i];
			}
		    }
		}

		if(min_yp.second == 0){
		    return false;
		}
		point down_min_yp = make_pair(min_yp.first, min_yp.second-1);
		point down_left_xp = make_pair(left_xp.first, left_xp.second-1);
		point down_right_xp = make_pair(right_xp.first, right_xp.second-1);
		if(m.find(down_min_yp)->second != 0){
		    return false;
		}
		if(m.find(down_left_xp)->second != 0){
		    return false;
		}
		if(m.find(down_right_xp)->second != 0){
		    return false;
		}
		return true;

	    }
	    return false;
	}

	void move(int nInput){
	    //97 a 100 d 115 s 120 x 101 e
	    if(nInput == 97){
		if(can_left()){
		    left();
		}
	    }

	    if(nInput == 100){
		if(can_right()){
		    right();
		}
	    }

	    if(nInput == 120){
		if(can_down()){
		    down_all();
		}
	    }

	    if(nInput == 115){
		if(can_down()){
		    down();
		}
	    }

	    if(nInput == 101){
		if(can_rotate()){
		    rotate();
		}
	    }

	    if(!can_down()){
		while(!movable_vec.empty()){
		    movable_vec.pop_back();
		}
		cur_type = 0;
	    }
	}

	bool can_make(int type){
	    if(type == 1){
		point p1 = make_pair(2 , 11);
		point p2 = make_pair(1 , 10);
		point p3 = make_pair(2 , 10);
		
		if(m.find(p1)->second != 0){
		    return false;
		} 
		if(m.find(p2)->second != 0){
		    return false;
		}
		if(m.find(p3)->second != 0){
		    return false;
		}
	    }
	    if(type == 2){
		point p1 = make_pair(2 , 11);
		point p2 = make_pair(2 , 10);
		point p3 = make_pair(2 , 9);
		
		if(m.find(p1)->second != 0){
		    return false;
		} 
		if(m.find(p2)->second != 0){
		    return false;
		}
		if(m.find(p3)->second != 0){
		    return false;
		}
	    }if(type == 3){
		point p1 = make_pair(2 , 11);
		point p2 = make_pair(1 , 10);
		point p3 = make_pair(2 , 10);
		point p4 = make_pair(3 , 10);
		point p5 = make_pair(2 , 9);
		if(m.find(p1)->second != 0){
		    return false;
		} 
		if(m.find(p2)->second != 0){
		    return false;
		}
		if(m.find(p3)->second != 0){
		    return false;
		}
		if(m.find(p4)->second != 0){
		    return false;
		}
		if(m.find(p5)->second != 0){
		    return false;
		}
	    }
	    return true;
	}

	void make(int type){
	    srand((unsigned int)time(0));
	    if(type == 1){
		point p1 = make_pair(2, 11);
		point p2 = make_pair(1, 10);
		point p3 = make_pair(2, 10);
		int random1 = rand()%4 + 1;
		int random2 = rand()%4 + 1;
		int random3 = rand()%4 + 1;
		m.find(p1)->second = random1;
		m.find(p2)->second = random2;
		m.find(p3)->second = random3;
		movable_vec.push_back(p1);
		movable_vec.push_back(p2);
		movable_vec.push_back(p3);
		cur_type = 1;
	    }
	    if(type == 2){
		point p1 = make_pair(2, 11);
		point p2 = make_pair(2, 10);
		point p3 = make_pair(2, 9);
		int random1 = rand()%4 + 1;
		int random2 = rand()%4 + 1;
		int random3 = rand()%4 + 1;
		m.find(p1)->second = random1;
		m.find(p2)->second = random2;
		m.find(p3)->second = random3;
		movable_vec.push_back(p1);
		movable_vec.push_back(p2);
		movable_vec.push_back(p3);
		cur_type = 2;
	    }
	    if(type == 3){
		point p1 = make_pair(2, 11);
		point p2 = make_pair(1, 10);
		point p3 = make_pair(2, 10);
		point p4 = make_pair(3, 10);
		point p5 = make_pair(2, 9);

		int random1 = rand()%4 + 1;
		int random2 = rand()%4 + 1;
		int random3 = rand()%4 + 1;
		int random4 = rand()%4 + 1;
		int random5 = rand()%4 + 1;
		m.find(p1)->second = random1;
		m.find(p2)->second = random2;
		m.find(p3)->second = random3;
		m.find(p4)->second = random4;
		m.find(p5)->second = random5;
		movable_vec.push_back(p1);
		movable_vec.push_back(p2);
		movable_vec.push_back(p3);
		movable_vec.push_back(p4);
		movable_vec.push_back(p5);
		cur_type = 3;
	    }

	}

	void gravity(){
	    /*
	     모든 좌표를 방문하면서 밑이 0이면 아래로 내림 12번반복;
	     */
	    for(int i = 0; i < 12; i++){
		for(int y=1; y<12; y++){
		    for(int x=0; x<5;x++){
			point down_p = make_pair(x,y-1);
			if(m.find(down_p)->second == 0){
			    point old_p = make_pair(x,y);
			    m.find(down_p)->second = m.find(old_p)->second;
			    m.find(old_p)->second = 0;
			}
		    }
		}
	    }
	}
	void print(){
	    cout << "**************************************"<<endl;

	    cout << endl;
	    cout << "SCORE : " << score <<endl;
	    cout << endl;
	    cout << endl;
	    for(int i = 11; i > -1; i--){
		for(int j = 0; j < 5; j++){
		    point p = make_pair(j, i);
		    cout << m.find(p)->second << "\t";
		}
		cout << endl;
		cout << endl;
		cout << endl;
	    }
	    cout << "**************************************"<<endl;
	}

};
