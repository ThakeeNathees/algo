
// https://leetcode.com/problems/longest-substring-without-repeating-characters/

struct Solution;

impl Solution {
  pub fn length_of_longest_substring(s: String) -> i32 {

    let length :usize = s.len();
    if length == 0 { return 0; }

    // contains[c] "returns" the index the char in the current substring if
    // it's exists otherwise -1.
    let mut contains :[i32; 256] = [-1; 256];

    // We keep track of two pointers start and end, indicating the current
    // substring.
    //
    // "foobarbaz"
    //  ^^
    //  |'--- end
    //  '---- start
    //
    let (mut start, mut end) :(usize, usize) = (0, 1);

    // Current substring is of length 1 and the first character is in the
    // substring.
    contains[s.as_bytes()[start] as usize] = 0;

    // The maximum length of all the substring we've seen so far.
    let mut result :i32 = 1;

    loop {
      if end == s.len() { return result; }

      // Index of the current character if it's exists in the current substring.
      let idx :i32 = contains[s.as_bytes()[end] as usize];
      if idx != -1 {
        // We've found a duplicate. Move the start pointer right next to the
        // duplicate. while doing so, pop all the characters along the way.
        // (ie. set index to -1).
        while start < (idx + 1) as usize {
          contains[s.as_bytes()[start] as usize] = -1;
          start += 1;
        }
      }

      // If the current character (ie. *end) is new set it's index otherwise
      // (ie. duplicate) update it.
      contains[s.as_bytes()[end] as usize] = end as i32;

      // Update the result.
      if ((end - start) as i32 + 1) > result {
        result = (end - start) as i32 + 1;
      };

      end += 1;
    }
  }
}

fn main() {
  println!(
    "{}",
    Solution::length_of_longest_substring("abba".to_string()));  
}
