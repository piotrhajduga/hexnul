#ifndef	_HEXNUL_PATHNODE_H_
#define	_HEXNUL_PATHNODE_H_

class PathNode {
    public:
        virtual bool isPassable() { return true; };
        virtual int getMoveCost() { return 0; };
};

#endif	/* _HEXNUL_PATHNODE_H_ */
