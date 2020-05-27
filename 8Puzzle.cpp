#include <bits/stdc++.h>

using namespace std;

class puzzle {
	public:
		int p[3][3];
		int f, g;

		puzzle(string st) {
			f = 0;
			g = 0;
			int k=0;
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					p[i][j] = st[k++] - '0';
				}
			}
		}

		void display() {
		    for(int i=0; i<3; i++) {
		        for(int j=0; j<3; j++) {
		            cout<<p[i][j]<<" ";
		        }
		        cout<<endl;
		    }
		}

		string to_string() {
		    string st = "123456780";
		    int k=0;
		    for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					st[k++] = p[i][j] + '0';
				}
			}
			return st;
			// cout<<"String: "<<st;
		}

		int tile_mismatch_count() {										//PART - 2	
			int count = 0;
			string goal = "123456780";
			string cur = to_string();
			for(int i=0; i<9; i++) {
				if(cur[i] != '0' && goal[i] != cur[i]) {
					count++;
				}
			}
			return count;
		}

		int manhattan_distance() {										//PART - 2
			int dist = 0;
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					switch(p[i][j]) {
						case 1: dist += abs(i - 0) + abs(j - 0); break;
						case 2: dist += abs(i - 0) + abs(j - 1); break;
						case 3: dist += abs(i - 0) + abs(j - 2); break;
						case 4: dist += abs(i - 1) + abs(j - 0); break;
						case 5: dist += abs(i - 1) + abs(j - 1); break;
						case 6: dist += abs(i - 1) + abs(j - 2); break;
						case 7: dist += abs(i - 2) + abs(j - 0); break;
						case 8: dist += abs(i - 2) + abs(j - 1); break;
					}
				}
			}
			return dist;
		}

		bool goal_test() {
			string goal = "123456780";
			string cur = to_string();
			if(goal == cur) {
				return 1;
			}
			return 0;
		}

		void update_f(int h) {
			if(!h) {
				f = 0;
				int tile_count = tile_mismatch_count();
				f = tile_count + g;
			}
			else {
				f = 0;
				int manh_distance = manhattan_distance();
				f = manh_distance + g;
			}
		}

		void initialize() {
			f = 0;
			g = 0;
		}

};

bool operator<(const puzzle& p1, const puzzle& p2) { 
  
    return p1.f > p2.f; 
}

priority_queue <puzzle> fringe;
unordered_set <string> visited;
int max_len, no_of_nodes;

bool isValid(int i, int j) {
	if(i>=0 && j>=0 && i<3 && j<3)
		return 1;
	else 
		return 0;
}

puzzle move(puzzle s, int i1, int j1, int i2, int j2) {
	string st = s.to_string();
	int index1 = i1*3+j1, index2 = i2*3+j2;
	char temp_char = st[index1];
	st[index1] = st[index2];
	st[index2] = temp_char;
	puzzle new_puz(st);
	return new_puz;
}

void expand(puzzle s, queue <puzzle> &queue_to_insert) {
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			if(s.p[i][j] == 0) {
				if(isValid(i-1, j)) {
					puzzle new_puz = move(s, i, j, i-1, j);
					if(visited.find(new_puz.to_string()) == visited.end()) {
						visited.insert(new_puz.to_string());
						new_puz.g++;
						no_of_nodes++;
						// cout<<"Pushed "<<new_puz.to_string()<<endl;
						queue_to_insert.push(new_puz);
					}
				}
				if(isValid(i+1, j)) {
					puzzle new_puz = move(s, i, j, i+1, j);
					if(visited.find(new_puz.to_string()) == visited.end()) {
						visited.insert(new_puz.to_string());
						new_puz.g++;
						no_of_nodes++;
						// cout<<"Pushed "<<new_puz.to_string()<<endl;
						queue_to_insert.push(new_puz);
					}
				}
				if(isValid(i, j-1)) {
					puzzle new_puz = move(s, i, j, i, j-1);
					if(visited.find(new_puz.to_string()) == visited.end()) {
						visited.insert(new_puz.to_string());
						new_puz.g++;
						no_of_nodes++;
						// cout<<"Pushed "<<new_puz.to_string()<<endl;
						queue_to_insert.push(new_puz);
					}
				}
				if(isValid(i, j+1)) {
					puzzle new_puz = move(s, i, j, i, j+1);
					if(visited.find(new_puz.to_string()) == visited.end()) {
						visited.insert(new_puz.to_string());
						new_puz.g++;
						no_of_nodes++;
						// cout<<"Pushed "<<new_puz.to_string()<<endl;
						queue_to_insert.push(new_puz);
					}
				}
				
			}
		}
	}

}

queue <puzzle> modified_expand(puzzle s, int depth) {
	queue <puzzle> temp1;
	expand(s, temp1);
	queue <puzzle> temp2(temp1);
	queue <puzzle> temp3;
	depth--;
	while(depth>0) {
		while(!temp2.empty()) {
			puzzle c = temp2.front();
			temp2.pop();
			expand(c, temp3);
			queue <puzzle> temp4(temp3);
			while(!temp4.empty()) {
				temp1.push(temp4.front());
				temp4.pop();
			}
		}
		depth--;
		while(!temp3.empty()) {
			temp2.push(temp3.front());
			temp3.pop();
		}
	}
	return temp1;
}

puzzle aStar(puzzle s, int h, int depth) {										//PART - 1
	
	max_len = 0;
	no_of_nodes = 0;
	s.initialize();
	visited.clear();
	visited.insert(s.to_string());
	fringe = priority_queue <puzzle>();
	
	while(!s.goal_test()) {
		queue <puzzle> mod_exp_result = modified_expand(s, depth);
		deque <puzzle> temp;
		while(!mod_exp_result.empty()) {
			temp.push_back(mod_exp_result.front());
			mod_exp_result.pop();
		}
		for(int i = 0; i < temp.size(); i++) {
			temp[i].update_f(h);
			fringe.push(temp[i]);
			if(fringe.size() > max_len) {
				max_len = fringe.size();
			}
		}
		if(!fringe.empty()) {
			s = fringe.top();
			fringe.pop();
		}
		else break;
		// g++;
	}
	if(s.goal_test())
		cout<<"Goal State Reached!"<<endl;
	else
		cout<<"Goal State not Reached!"<<endl;

	cout<<"Maximum fringe length: "<<max_len<<endl;							//PART - 5
	cout<<"No. of nodes: "<<no_of_nodes<<endl;								//PART - 5
	return s;
}

int main() {
	int depth;
	int rand_gen_initial_states = 10;										//PART - 4
	cout<<"Enter Depth: ";
	cin>>depth;
	
	// UNCOMMENT LINES MARKED (1)-(4) AND COMMENT LINES MARKED (5)-(7) FOR GENERATING ONLY VALID INPUT STATES.

	// srand ( time(NULL) ); //-----(1)
	// const string input_Arr[20] = {"413705826", "813402765", "246583017", "038145672", "301682475", "182043765", "301682475", "361285047", "261705834", "203714568", "501837264", "725368401", "157820643", "713248650", "274518306", "437165280", "452710836", "062537481", "804125376", "235107846"}; //-----(2)
	
	while(rand_gen_initial_states--) { 										//PART - 4
		// int RandIndex = rand() % 20; //-----(3)
		// puzzle s(input_Arr[RandIndex]); //-----(4)
		
		string input = "123456780"; //-----(5)
		random_shuffle(input.begin(), input.end()); //-----(6)				//PART - 4
		puzzle s(input); //-----(7)
	
		cout<<endl<<"-----------------------------------------------------"<<endl;
		cout<<"                       ROUND "<<10-rand_gen_initial_states;
		cout<<endl<<"-----------------------------------------------------"<<endl;
		cout<<"Initial State: "<<endl;
		s.display();
		cout<<endl;
		cout<<endl<<"Depth 1 using Tile Mismatch Count: "<<endl;
		aStar(s, 0, 1);														//PART - 3
		cout<<endl<<"Depth "<<depth<<" using Tile Mismatch Count: "<<endl;
		aStar(s, 0, depth);														//PART - 3
		cout<<endl<<"Depth 1 using Manhattan Distance: "<<endl;
		aStar(s, 1, 1);														//PART - 3
		cout<<endl<<"Depth "<<depth<<" using Manhattan Distance: "<<endl;
		aStar(s, 1, depth);														//PART - 3

	}
	return 0;
}
