class Polynomial
{
	int n, *deg, numroots ;
	double *cof , *root ;
	public:
		void roots();								// Initialize the numroots and root array.
		Polynomial();								// initialize a zero polynomial
		~Polynomial();
		Polynomial(const Polynomial &source);
		void read();						
		void print();								//Print the polynomial
		double valueAt(const double a);				//put the value a in x and then calculate the value
		double valueat(const double a);				//at first i defined function as "valueat" but in problem statement it is "valueAt" so i didnt remove this one bcoz it is used in all other functions
		Polynomial integral();						//integrates with constant of integration as zero
		Polynomial derivative();					//returns derivative
		bool is_root(double a, double b);			//returns true if polynomial has root in (a,b).
		double rootbetween(double a,double b);		//returns the root in [a,b]. I've made sure that there's only one root in [a,b] before calling this function.
		void print_root();							//prints all the roots
		void plot (double x1,double x2);			//plots the graph between x1 and x2. Also it scales the graph so that it fixes in the Canvas screen
		Polynomial operator+(const Polynomial& p);	
		Polynomial operator-(Polynomial p);			
		Polynomial operator*(Polynomial p);			
		Polynomial operator/(Polynomial dividend);	//Return quotient of polynomial
		Polynomial operator%(Polynomial dividend);	//Return remainder of polynomial
		double maximum (double x1,double x2);		//returns absolute maximum of polynomial function in [a,b]
		double minimum (double x1,double x2);		//returns absolute minimum of polynomial function in [a,b]
		void operator = (const Polynomial &p);		
};