```c++
struct Bid {
	private:
		std::string bidId;
		double amount;
	public:
		Bid(double amount = 0) { //default value for parameter amount
			this->amount = amount;
		}
		//DELEGATING CONSTRUCTOR
		//This is a delegating constructor. It calls another constructor for this class to avoid redundant code. But it cannot initialize members.
	    Bid(std::string bidId) : Bid(0) {
	        this->bidId = bidId;
	    }

		//INITIALIZER LIST
		//We can initialize members 
		Bid(std::string id, double sum) : bidId(id), amount(sum) {}
}
```