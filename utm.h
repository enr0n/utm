/*
 * Header file for Universal Turing Machine Simulator
 */
#include <string>
class UTM {
/*
 * Declare constants
 */
static const int START=1;
static const int LEFT_BLANK=0;
/*
 * Read/write chars
 */
static const char ONE='1';
static const char BLANK='B';
static const char LEFT='L';
static const char RIGHT='R';
public:
	UTM(int n,std::string str);
	~UTM();
	std::string run();
	void addInstruction(int s,char r,char w, int n);
	struct four_tuple {
		int id;
		int start_state;
		char read;
		char write;
		int next_state;
	};
private:
	/*
	 * Declare global variables
	 */
	bool halted;
	/*
	 * This is needs to be a variable rather than a constant
	 * like its left-sided counterpart.
	 */
	int RIGHT_BLANK;
	/*
	 * Variables for the machine state
	 * and position of the r/w head.
	 */
	int m_state;
	int head_pos;
	/*
	 * Keeps track of 4-tuple IDs. Used to assist with simulating.
	 */
	int cur_id;
	/*
	 * TM specification variables
	 */
	four_tuple *m;
	std::string tape;
	int size;
    /*
	 * Methods for the r/w head
	 */
	void extend_left();
	void extend_right();
	void L();
	void R();
	void one();
	void blank();
	void write(int id);
	void exec(int id);
	void halt();
	
	char read();

	int find();
};
