
// https://leetcode.com/problems/regular-expression-matching/

impl Solution {
  pub fn is_match(s: String, p: String) -> bool {

    let I = s.len();
    let J = p.len();
    let mut dp :Vec<Vec<bool>> = vec![vec![false; J+1]; I+1];
    dp[I][J] = true;

    for i in (0..s.len()+1).rev() {
      for j in (0..p.len()+1).rev() {
        if i == I && j == J { continue; }
        
        let first_match = (i < I) && (j < J) && (
          s.chars().nth(i) == p.chars().nth(j) ||
          p.chars().nth(j).unwrap() == '.');

        if j + 1 < J && p.chars().nth(j + 1).unwrap() == '*' {
          dp[i][j] = dp[i][j+2] || (first_match && dp[i+1][j]);
        } else {
          dp[i][j] = first_match && dp[i+1][j+1];
        }
      }
    }
    return dp[0][0];
  }
}
