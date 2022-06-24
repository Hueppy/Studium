using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class User
{
    public User()
    {
        FriendRequestSenders = new HashSet<FriendRequest>();
        FriendRequestReceivers = new HashSet<FriendRequest>();
        Messages = new HashSet<Message>();
        PictureUsers = new HashSet<PictureUser>();
        Pictures = new HashSet<Picture>();
        Posts = new HashSet<Post>();
        RatingSenders = new HashSet<Rating>();
        RatingUsers = new HashSet<Rating>();
        ReportSenders = new HashSet<Report>();
        ReportUsers = new HashSet<Report>();
        Chatrooms = new HashSet<Chatroom>();
    }

    public int Id { get; set; }
    public string Name { get; set; } = null!;
    public string Telephone { get; set; } = null!;
    public string Email { get; set; } = null!;
    [JsonIgnore]
    public int AddressId { get; set; }
    public bool Active { get; set; }
    public DateTime LockedUntil { get; set; }
    public UserStatus Status { get; set; }

    public virtual Address Address { get; set; } = null!;
    [JsonIgnore]
    public virtual ICollection<FriendRequest> FriendRequestReceivers { get; set; }
    [JsonIgnore]
    public virtual ICollection<FriendRequest> FriendRequestSenders { get; set; }
    [JsonIgnore]
    public virtual Login? Login { get; set; } = null!;
    [JsonIgnore]
    public virtual ICollection<Message> Messages { get; set; }
    [JsonIgnore]
    public virtual ICollection<PictureUser> PictureUsers { get; set; }
    [JsonIgnore]
    public virtual ICollection<Picture> Pictures { get; set; }
    [JsonIgnore]
    public virtual ICollection<Post> Posts { get; set; }
    [JsonIgnore]
    public virtual ICollection<Rating> RatingSenders { get; set; }
    [JsonIgnore]
    public virtual ICollection<Rating> RatingUsers { get; set; }
    [JsonIgnore]
    public virtual ICollection<Report> ReportSenders { get; set; }
    [JsonIgnore]
    public virtual ICollection<Report> ReportUsers { get; set; }

    [JsonIgnore]
    public virtual ICollection<Chatroom> Chatrooms { get; set; }
}
