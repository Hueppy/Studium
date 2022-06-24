using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class FriendRequest
{
    public int Id { get; set; }
    public DateTime SendAt { get; set; }
    public DateTime SeenAt { get; set; }
    public int SenderId { get; set; }
    public int ReceiverId { get; set; }
    public FriendRequestState State { get; set; }

    [JsonIgnore]
    public virtual User Receiver { get; set; } = null!;
    [JsonIgnore]
    public virtual User Sender { get; set; } = null!;
}
