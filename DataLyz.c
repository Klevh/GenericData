#include "DataLyz.h"

DataLyz newDataLyz(size_t n, ...){
    va_list l;
    DataLyz t = {0,0,0,0};
    size_t size = 0, old = 0, i = 0;
    
    t.sizes = (size_t*)malloc(n*sizeof(size_t));
    
    if(t.sizes){
        t.size = n;
        va_start(l,n);
        while(i < n){
            size = va_arg(l,size_t);
            t.sizes[i] = old;
            old += size;
            ++i;
        }
        va_end(l);
        
        t.ptr_size = old;
        t.ptr = malloc(old*sizeof(char));
        
        if(!t.ptr){
            free(t.sizes);
            t.sizes = NULL;
            t.ptr_size = 0;
        }
    }
    
    return t;
}

int isAllocDataLyz(DataLyz t){
    return t.ptr && t.sizes && t.ptr_size;
}

void * getDataLyz(DataLyz lyz, size_t size){
    if(size >= lyz.size)
	return NULL;
    return lyz.ptr + lyz.sizes[size];
}

void freeDataLyz(DataLyz t){
    if(t.sizes)
        free(t.sizes);
    if(t.ptr)
        free(t.ptr);
}

DataLyz copyDataLyz(DataLyz lyz){
    DataLyz cp = {0,0,0,0};
    size_t i;
    
    if(isAllocDataLyz(lyz)){
        cp.sizes = (size_t*)malloc(sizeof(size_t)*lyz.size);
        
        if(cp.sizes){
            cp.ptr = malloc(lyz.ptr_size);
            
            if(cp.ptr){
                for(i = 0; i < lyz.size; ++i)
                    cp.sizes[i] = lyz.sizes[i];
		memcpy(cp.ptr,lyz.ptr,lyz.ptr_size);
                cp.size = lyz.size;
                cp.ptr_size = lyz.ptr_size;
            }else{
                free(cp.sizes);
                cp.sizes = NULL;
            }
        }
    }
    
    return cp;
}

DataLyz loadDataLyz(char * file_path){
    FILE    * fp;
    DataLyz   lyz = {0,0,0,0};

    if(file_path){
	fp = fopen(file_path,"rb");
	if(fp){
	    fread(&(lyz.ptr_size), sizeof(lyz.ptr_size), 1, fp);
	    fread(&(lyz.size), sizeof(lyz.size), 1, fp);

	    lyz.ptr = malloc(lyz.ptr_size);

	    if(lyz.ptr){
		lyz.sizes = malloc(lyz.size * sizeof(*(lyz.sizes)));

		if(lyz.sizes){
		    fread(lyz.ptr, lyz.ptr_size, 1, fp);
		    fread(lyz.sizes, sizeof(*(lyz.sizes)) * lyz.size, 1, fp);
		}else{
		    free(lyz.ptr);
		    lyz.ptr_size = 0;
		    lyz.size     = 0;
		    lyz.ptr      = NULL;
		}
	    }else{
		lyz.ptr_size = 0;
		lyz.size     = 0;
	    }

	    fclose(fp);
	}
    }

    return lyz;
}

int saveDataLyz(char * file_path,DataLyz lyz){
    FILE * fp;
    int    err = 1;

    if(file_path){
	fp = fopen(file_path,"wb");
	if(fp){
	    err = 0;

	    fwrite(&(lyz.ptr_size), sizeof(lyz.ptr_size), 1, fp);
	    fwrite(&(lyz.size), sizeof(lyz.size), 1, fp);
	    fwrite(lyz.ptr, lyz.ptr_size, 1, fp);
	    fwrite(lyz.sizes, sizeof(*(lyz.sizes)) * lyz.size, 1, fp);

	    fclose(fp);
	}
    }

    return err;
}
