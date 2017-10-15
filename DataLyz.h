#ifndef _DATALYZ_DATASAVER_KLEVH_
#define _DATALYZ_DATASAVER_KLEVH_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct DataLyz{
    void * ptr;
    size_t * sizes;
    size_t size;
    size_t ptr_size;
}DataLyz;

/**
 * @brief Construct a new DataLyz
 * @param n : number of elements in the DataLyz
 * @param ... : n sizes of type size_t corresponding to the size in bytes of each element
 * @return A DataLyz (correctly created or not)
 */
DataLyz newDataLyz(size_t n,...);

/**
 * @brief Tell's wether a DataLyz was correctly created or not
 * @return 1 if it was, 0 if not
 */
int isAllocDataLyz(DataLyz t);

/**
 * @brief Return the (size + 1)th element of the DataLyz
 * @param lyz : DataLyz from which we want to get an element
 * @param size : index of the element in the DataLyz
 * @return A pointer pointing to the (size + 1)th element of the DataLyz on success, NULL on failure
 */
void * getDataLyz(DataLyz lyz,size_t size);

/**
 * @brief Free the memory allocated to a DataLyz
 * @param lyz : DataLyz to be freed
 */
void freeDataLyz(DataLyz lyz);

/**
 * @brief Creates a copy of a DataLyz
 * @param lyz : DataLyz to be copied
 * @return The copy of the DataLyz passed as a parameter on success, a not allocated DataLyz on failure
 */
DataLyz copyDataLyz(DataLyz lyz);

/**
 * @brief Load a DataLyz from a file
 * @param file_path : path of the binary file to read the DataLyz from
 * @return The DataLyz loaded from the file on success, a not allocated DataLyz on failure
 */
DataLyz loadDataLyz(char * file_path);

/**
 * @brief Save a DataLyz from a file
 * @param file_path : path of the binary file to write the DataLyz from
 * @param lyz : DataLyz to be saved
 * @return 1 if it failed, 0 if not
 */
int saveDataLyz(char * file_path,DataLyz lyz);

#endif
