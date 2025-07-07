#include "LogScMatrix.hpp"
#define TS_MULTIPLY(C1,C2,C3) template<typename T> constexpr void MatrixMultiplySp<T,C1,C2,C3>::multiply(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result) noexcept{

namespace LogSc  {
    // 1. 2×2 × 2×2 -> 2×2
    TS_MULTIPLY(2, 2, 2) 
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];

        result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
        result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];
    }
    // 2. 2×2 × 2×3 -> 2×3
    TS_MULTIPLY(2, 2, 3)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
    }
    // 3. 2×2 × 2×4 -> 2×4
    TS_MULTIPLY(2, 2, 4) 
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3];
    }
    // 4. 2×3 × 3×2 -> 2×2
    TS_MULTIPLY(2, 3, 2) 
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
    }
    // 5. 2×3 × 3×3 -> 2×3
    TS_MULTIPLY(2, 3, 3)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];
    }
    // 6. 2×3 × 3×4 -> 2×4
    TS_MULTIPLY(2, 3, 4)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3];
    }
    // 7. 2×4 × 4×2 -> 2×2
    TS_MULTIPLY(2, 4, 2) 
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
    }
    // 8. 2×4 × 4×3 -> 2×3
    TS_MULTIPLY(2, 4, 3)  
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];
    }
    // 9. 2×4 × 4×4 -> 2×4
    TS_MULTIPLY(2, 4, 4)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3] + lhs[0][3]*rhs[3][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3] + lhs[1][3]*rhs[3][3];
    }
    // 10. 3×2 × 2×2 -> 3×2
    TS_MULTIPLY(3, 2, 2)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
    }
    // 11. 3×2 × 2×3 -> 3×3
    TS_MULTIPLY(3, 2, 3)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
        
        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2];
    }
    // 12. 3×2 × 2×4 -> 3×4
    TS_MULTIPLY(3, 2, 4)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3];
        
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3];
    }
    // 13. 3×3 × 3×2 -> 3×2
    TS_MULTIPLY(3, 3, 2)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        
        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
    }
    // 14. 3×3 × 3×3 -> 3×3
    TS_MULTIPLY(3, 3, 3)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2];
    }
    // 15. 3×3 × 3×4 -> 3×4
    TS_MULTIPLY(3, 3, 4)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3];
    }
    // 16. 3×4 × 4×2 -> 3×2
    TS_MULTIPLY(3, 4, 2)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
    }
    // 17. 3×4 × 4×3 -> 3×3
    TS_MULTIPLY(3, 4, 3)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2];
    }
    // 18. 3×4 × 4×4 -> 3×4
    TS_MULTIPLY(3, 4, 4)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3] + lhs[0][3]*rhs[3][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3] + lhs[1][3]*rhs[3][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3] + lhs[2][3]*rhs[3][3];
    }
    // 19. 4×2 × 2×2 -> 4×2
    TS_MULTIPLY(4, 2, 2)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1];
    }
    // 20. 4×2 × 2×3 -> 4×3
    TS_MULTIPLY(4, 2, 3)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2];
    }
    // 21. 4×2 × 2×4 -> 4×4
    TS_MULTIPLY(4, 2, 4)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2];
        result[3][3] = lhs[3][0]*rhs[0][3] + lhs[3][1]*rhs[1][3];
    }
    // 22. 4×3 × 3×2 -> 4×2
    TS_MULTIPLY(4, 3, 2)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1];
    }
    // 23. 4×3 × 3×3 -> 4×3
    TS_MULTIPLY(4, 3, 3)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2];
    }
    // 24. 4×3 × 3×4 -> 4×4
    TS_MULTIPLY(4, 3, 4)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2];
        result[3][3] = lhs[3][0]*rhs[0][3] + lhs[3][1]*rhs[1][3] + lhs[3][2]*rhs[2][3];
    }
    // 25. 4×4 × 4×2 -> 4×2
    TS_MULTIPLY(4, 4, 2)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0] + lhs[3][3]*rhs[3][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1] + lhs[3][3]*rhs[3][1];
    }
    // 26. 4×4 × 4×3 -> 4×3
    TS_MULTIPLY(4, 4, 3)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0] + lhs[3][3]*rhs[3][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1] + lhs[3][3]*rhs[3][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2] + lhs[3][3]*rhs[3][2];
    }
    // 27. 4×4 × 4×4 -> 4×4
    TS_MULTIPLY(4, 4, 4)
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3] + lhs[0][3]*rhs[3][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3] + lhs[1][3]*rhs[3][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3] + lhs[2][3]*rhs[3][3];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0] + lhs[3][3]*rhs[3][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1] + lhs[3][3]*rhs[3][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2] + lhs[3][3]*rhs[3][2];
        result[3][3] = lhs[3][0]*rhs[0][3] + lhs[3][1]*rhs[1][3] + lhs[3][2]*rhs[2][3] + lhs[3][3]*rhs[3][3];
    }
};