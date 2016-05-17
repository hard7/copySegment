#ifndef COPYSEGMENT_CUDA_TYPES_H
#define COPYSEGMENT_CUDA_TYPES_H


namespace cudaType {
    struct Point { int x, y, z, w; };
    struct Box { Point lo, width; };
}


#endif //COPYSEGMENT_CUDA_TYPES_H
