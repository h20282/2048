#include <cstdlib>

#include <iostream>
#include <vector>
#include <map>

constexpr int kSize = 4;

struct Point{ int x; int y; };
bool operator == (Point a, Point b) { return a.x==b.x && a.y==b.y; }
bool operator != (Point a, Point b) { return !(a==b); }
bool operator <  (Point a, Point b) { return a.x==b.x ? a.x<b.x : a.y<b.y; }
Point operator + (Point a, Point b) { return {a.x+b.x, a.y+b.y}; }

inline int GetPos(int x, int y) { return y*kSize+x; }
inline int GetPos(Point p) { return GetPos(p.x, p.y); }

/**
 * @brief {0, 4, 2, 2} -> {4, 4, 0, 0}
 *
 * @param arr    kSize 个指向一行|一列数字的指针 
 */
void DoMove(int **arr){
	for (int i=0; i<kSize; ++i) {
		int &curr = *arr[i];
		for (int j=i+1; j<kSize; j++){
			if (*arr[j] == curr){
				*arr[j] = 0;
				curr *= 2;
				break;
			}
			if (*arr[j] != 0) {
				break;
			}
		}
	}
	
	for (int t=0; t<kSize; ++t) {
		for (int i=0; i<kSize-1; ++i) {
			int &curr = *arr[i];
			if (curr==0) {
				curr = *arr[i+1];
				*arr[i+1] = 0;
			}
		}
	}
	// todo: return moved or not
}

/**
 * @brief 对begin为起点，adder为方向的kSize个数字进行移动，移动方向为朝向begin
 * 	        
 * 	        坐标系：  +----> x
 * 	                  | 
 * 	                  |  1 2 3 4
 * 	                 y|  5 6 7 8
 * 	                  v  ...
 * 
 * @param base 所有数字的首地址，数字从上到下，从左到右排列
 *
 * @param begin 起始点
 *
 * @param adder 迭代方向
 */
void DoMove(int *base, Point begin, Point adder) {
	Point p_arr[kSize];
	Point p = begin;
	for (int i=0; i<kSize; ++i, p=p+adder) {
		p_arr[i] = p;
	} 
	int *arr[kSize];
	for (int i=0; i<kSize; ++i) {
		arr[i] = base + GetPos(p_arr[i]);
	}
	DoMove((int**)&arr);
}

enum Dir{ kUp, kRight, kDown, kLeft };

/**
 * @brief 向方向dir移动
 *
 * @param arr 所有数字的首地址
 *
 * @param dir 移动方向
 */
void DoMove(int *arr, Dir dir) {
	if (dir==kUp) {
		for (int x=0; x<kSize; ++x) {
			DoMove(arr, {x, 0}, {0, 1});
		}
	} else if (dir==kDown) {
		for (int x=0; x<kSize; ++x) {
			DoMove(arr, {x, kSize-1}, {0, -1});
		}
	} else if (dir==kLeft) {
		for (int y=0; y<kSize; ++y) {
			DoMove(arr, {0, y}, {1, 0});
		}
	} else if (dir==kRight) {
		for (int y=0; y<kSize; ++y) {
			DoMove(arr, {kSize-1, y}, {-1, 0});
		}
	}
}

void Test1(){
	int arr[kSize];
	int *arr_p[kSize];
	for (int i=0; i<kSize; ++i) {
		arr_p[i] = arr+i;
	}
	while(true){
		for ( int i=0; i<kSize; ++i) { std::cin>>arr[i]; }
		DoMove((int**)&arr_p);
		for ( int i=0; i<kSize; ++i) { std::cout<<arr[i]<<" "; }
		std::cout << std::endl;
	}
}

int main(){
	int arr[kSize*kSize] = {0};
	std::map<char, Dir> char2Dir;
	char2Dir['w'] = kUp;
	char2Dir['s'] = kDown;
	char2Dir['a'] = kLeft;
	char2Dir['d'] = kRight;
	
	while (1) {
		// todo: 添加`game over` 的判定（不再能移动）
		int idx;
		do{idx = rand() % (kSize*kSize); }while(arr[idx]!=0);
		arr[idx] = 2;
		
		for (int y=0; y<kSize; ++y) {
			for (int x=0; x<kSize; ++x) {
				printf("%6d", arr[GetPos(x,y)]);
			}
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}
		
		char c;
		std::cin>>c;

		if (char2Dir.find(c) == char2Dir.end()) { continue; }
		DoMove(arr, char2Dir[c]);

	}
}
