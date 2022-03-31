int f(int i)
{
   if (i<=1) return 1;
   else return f(i-1)+f(i-2);  
}
 
// 
// SWITCHES TO 
//

int f(int i)
{
   static int memo[MAX]={1,1};
   if (memo[i]) return memo[i];
   else return memo[i]=f(i-1)+f(i-2);  
}
