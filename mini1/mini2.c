#define TRUE (1==1)
#define FALSE (!TRUE)

typedef struct tagPOINT
{
    int  x;
    int  y;
} POINT;

int isRightTriangle (POINT A, POINT B, POINT C) {
    int AB2 = (B.x - A.x)*(B.x - A.x) + (B.y - A.y) * (B.y - A.y);
    int BC2 = (B.x - C.x)*(B.x - C.x)+ (B.y - C.y) * (B.y - C.y);
    int CA2 = (C.x - A.x)*(C.x - A.x) + (C.y - A.y)*(C.y - A.y);

    if (AB2 + BC2 == CA2 || AB2 + CA2 == BC2 || CA2 + BC2 == AB2) {
        return TRUE;
    } else {
        return FALSE;
    }
}


