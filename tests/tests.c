#include "tests.h"

void test1(){
    DataLyz lyz = newDataLyz(3, sizeof(int), sizeof(char), sizeof(double));
    
    if(isAllocDataLyz(lyz)){
        *(int*)getDataLyz(lyz,0) = 5;
        *(char*)getDataLyz(lyz,1) = 'A';
        *(double*)getDataLyz(lyz,2) = 5.3;

	assert( *(int*)getDataLyz(lyz,0) == 5 );
	assert( *(char*)getDataLyz(lyz,1) == 'A' );
	assert( *(double*)getDataLyz(lyz,2) == 5.3 );
	assert( getDataLyz(lyz,3) == NULL );
        
        freeDataLyz(lyz);
    }else
        printf("Allocation Error in test 1\n");
}

void test2(){
    DataLyz lyz = newDataLyz(3, sizeof(int), sizeof(char), sizeof(double));
    DataLyz l2;
    
    if(isAllocDataLyz(lyz)){
        *(int*)getDataLyz(lyz,0) = 5;
        *(char*)getDataLyz(lyz,1) = 'A';
        *(double*)getDataLyz(lyz,2) = 5.3;
        
        l2 = copyDataLyz(lyz);
        if(isAllocDataLyz(l2)){
            *(int*)getDataLyz(l2,0) = 2;
	    
	    assert( *(int*)getDataLyz(l2,0) == 2 );
	    assert( *(char*)getDataLyz(l2,1) == 'A' );
	    assert( *(double*)getDataLyz(l2,2) == 5.3 );
	    assert( getDataLyz(l2,3) == NULL );

	    assert( *(int*)getDataLyz(lyz,0) == 5 );
	    assert( *(char*)getDataLyz(lyz,1) == 'A' );
	    assert( *(double*)getDataLyz(lyz,2) == 5.3 );
	    assert( getDataLyz(lyz,3) == NULL );
            
            freeDataLyz(l2);
        }else
            printf("\nFailed to allocate the copy in test 2\n");
        
        freeDataLyz(lyz);
    }else
        printf("Allocation Error in test 2\n");
}

void test3(){
    DataLyz lyz = newDataLyz(3, sizeof(int), sizeof(char), sizeof(double));
    DataLyz l2;
    
    if(isAllocDataLyz(lyz)){
        *(int*)getDataLyz(lyz,0) = 5;
        *(char*)getDataLyz(lyz,1) = 'A';
        *(double*)getDataLyz(lyz,2) = 5.3;
	
	assert( !saveDataLyz("text.bin",lyz) );

	l2 = loadDataLyz("text.bin");

	assert( isAllocDataLyz(l2) );
	assert( *(int*)getDataLyz(l2,0) == 5 );
	assert( *(char*)getDataLyz(l2,1) == 'A' );
	assert( *(double*)getDataLyz(l2,2) == 5.3 );
	assert( getDataLyz(l2,3) == NULL );
    }else
        printf("Allocation Error in test 3\n");
}

void all_tests(){
    puts("Test 1 : DataLyz getter and setter" RED);
    test1();
    puts(GREEN "\tTest 1 went well\n");
    
    puts(NORMAL "Test 2 : DataLyz copy" RED);
    test2();
    puts(GREEN "\tTest 2 went well\n");
    
    puts(NORMAL "Test 3 : DataLyz load/save from file" RED);
    test3();
    puts(GREEN "\tTest 3 went well\n");

    puts("All tests went well !" NORMAL);
}
