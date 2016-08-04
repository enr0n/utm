#include "utm.h"
#include <iostream>
#include <cstdlib>
using namespace std;
/*
 * Universal Turing Machine Simulator
 */
UTM::UTM(int n,string str) : cur_id(0),halted(false){
	tape = str;
	size = n;
	m = new UTM::four_tuple[size];
}

UTM::~UTM() {
	delete m;
}

void UTM::addInstruction(int s,char r,char w,int n) {
	int temp = cur_id;
	m[temp].id=cur_id;
	m[temp].start_state=s;
	m[temp].read=r;
	m[temp].write=w;
	m[temp].next_state=n;
	cur_id++;
}

void UTM::extend_left() {
	tape=BLANK+tape;
}

void UTM::extend_right() {
	tape=tape+BLANK;
}

void UTM::L() {
	if (head_pos != LEFT_BLANK) {
		head_pos--;
	} else {
		extend_left();
	}
}

void UTM::R() {
	if (head_pos != RIGHT_BLANK) {
		head_pos++;
	} else {
		extend_right();
		head_pos++;
	}
}

void UTM::one() {
	tape.at(head_pos)=ONE;
}

void UTM::blank() {
	tape.at(head_pos)=BLANK;
}

void UTM::write(int id) {
	char e = m[id].write;
	switch (e) {
		case LEFT:
			L();break;
		case RIGHT:
			R();break;
		case ONE:
			one();break;
		case BLANK:
			blank();break;
	}
}

void UTM::halt() {
	halted=true;
}

char UTM::read() {
	return tape.at(head_pos);
}

int UTM::find() {
	int temp = cur_id;
	for (int i=0;i < temp; i++) {
		if (m[i].start_state == m_state &&
	        m[i].read == read() ) {
			return m[i].id;
		}
	}
	return -1;
}

void UTM::exec(int id) {
	write(id);
	m_state = m[id].next_state;
}
 
string UTM::run() {
	/*
	 * add 'blanks' to tape 
     */
	tape=BLANK+tape+BLANK;
	/*
	 * init global variables
	 */
	m_state=0;
	head_pos=START;
	RIGHT_BLANK=tape.length()-1;

	while (!halted) {
		int id = find();
		if (id != -1) {
			exec(id);
		} else {
			halt();
		}
	}
	return tape;
}
