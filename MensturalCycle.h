#pragma once
#include <string>
#include <vector>
using namespace std;

// Prototype Objects
// Stage
class MoodSwing {
public:
	MoodSwing(int mood);
	~MoodSwing();

	void activateMoodSwing();
private:
	int mMood; // Associated value from a mood key-value table
};

class Stage {
public:
	Stage(string name, vector<MoodSwing> moodSwings);
	~Stage();

	void activateMoodSwing();
	string getName;
private:
	vector<MoodSwing> mMoodSwings;
	string mName;
};

class Action {
public:
	Action(string name, bool involvesOtherSim /*Animation animation*/);
	~Action();

	void act();
private: 
	// Animation animation; This imaginary class would associate a specific animation with the action
};

class Product {
public:
	Product(string name, int hoursUsable, int price);
	~Product();

	void buy_product();
	int use_product(); // Returns hoursUsable to let player know how many hours they have before they have to change product
private:
	int mPrice, hoursUsable;
	string mName;
};

// Main Class

class MensturalCycle {
public:
	MensturalCycle(vector<Product> ContainedProducts, vector<Action> actions);

	vector<Action> getActions();
	vector<Product> getProductsInInventory();
	void switchStage(Stage stage);
private:
	vector<Product> mContainedProducts;
	Stage mCurrentStage = Stage("Mensturation", {});
	bool mActive = false; // Cycle starts inactive until first mensturation event.
};