@__format = internal global [7 x i8] c"%d %d\0A\00"

declare i32 @printf(ptr, ...)

define i32 @main() {
0:
  br label %1

1:
  %2 = phi i32 [ 42, %0 ], [ %3, %1 ]
  %3 = phi i32 [ 43, %0 ], [ %2, %1 ]
  %4 = phi i1 [ true, %0 ], [ false, %1 ]
  br i1 %4, label %1, label %5

5:
  %6 = call i32 @printf(ptr @__format, i32 %2, i32 %3)
  ret i32 0
}
