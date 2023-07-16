#pragma once
 class TREE {
 public:

	virtual void add(int value) {

	 }

	virtual int deleteRoot(){
		return 0;
	}
	virtual int findvalue(int value) {
		return 0;
	}
	virtual void clear() {

	}
	virtual void visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn) {

	}

	void prepareVisulaisation() {
		{
			std::string cR, cL, cP;
			cR = cL = cP = "  ";
			cR[0] = 218; cR[1] = 196;
			cL[0] = 192; cL[1] = 196;
			cP[0] = 179;



			visualisation(cR, cL, cP, "", "");
		}
	}

};