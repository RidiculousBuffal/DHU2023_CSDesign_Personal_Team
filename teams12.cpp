#include<bits/stdc++.h>
using namespace std;
struct news
{
    int name;
    int time;//记录发送时间
    int post;//推文
    news(){ }
    news(int name,int time,int post)
    {
        this->name=name;
        this->time=time;
        this->post=post;
    }
};
bool operator < (news x ,news y)
{
    return x.time>y.time;
}
class Twitter
{
protected:
    set<news>pos;//存放新闻
    map<int,deque<int>> followers;//自己关注的人
    int Time;
public:
    Twitter(){Time=0;}
    void postTweet(int userId,int tweetId)
    {
        pos.insert({userId,++Time,tweetId});
    }
    vector<int>getNewsFeed(int userId)
    {
        vector<int>res;
        int k=0;
        for(auto it=pos.begin();it!=pos.end();it++)
        {
            if(k>=10){return res;}
            else
            {
                if(it->name==userId||find(followers[userId].begin(),followers[userId].end(),it->name)!=followers[userId].end())
                {
                    k++;
                    res.push_back(it->post);
                }
            }
        }
        return res;
    }
    void follow(int followerId,int followeeId)
    {
        //关注用户
        followers[followerId].push_back(followeeId);
    }
    void unfollow(int followerId,int followeeId)
    {
        if(followers.count(followerId)!=0) {
            std::deque<int>::iterator it=find(followers[followerId].begin(), followers[followerId].end(), followeeId);
            if(it!=followers[followerId].end()) { followers[followerId].erase(it); }
        }
    }
};
int main()
{
    Twitter twitter;
 //ifstream cin("5000.txt");
    string s;
    while(cin>>s)
    {
        if(s=="postTweet")
        {
            int UserId,TweetId;
            cin>>UserId>>TweetId;
            twitter.postTweet(UserId,TweetId);
        }
        else if(s=="getNewsFeed")
        {
            int UserId;
            cin>>UserId;
            vector<int>res=twitter.getNewsFeed(UserId);
            for(auto x : res)
            {
                cout<<x<<" ";
            }
            cout<<endl;
        }
        else if(s=="follow")
        {
            int followerId,followeeId;
            cin>>followerId>>followeeId;
            twitter.follow(followerId,followeeId);
        }
        else if(s=="unfollow")
        {
            int followerId,followeeId;
            cin>>followerId>>followeeId;
            twitter.unfollow(followerId,followeeId);
        }
    }
    return 0;
}