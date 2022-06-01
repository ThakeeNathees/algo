
// https://leetcode.com/problems/trapping-rain-water/

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

int stack[2 * 10000 + 1];

int trap(int* height, int heightSize) {

  int ans = 0;
  int sp = 0;
  for (int i = 0; i < heightSize; i++) {
    while (sp > 0 && height[stack[sp - 1]] < height[i]) {
      int top = stack[--sp];
      if (sp == 0) break;
      int prev = stack[sp - 1];
      int dist = i - prev - 1;
      ans += (MIN(height[prev], height[i]) - height[top]) * dist;
    }
    stack[sp++] = i;
  }

  return ans;
}
