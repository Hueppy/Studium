using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Message
{
    public int Id { get; set; }
    public DateTime? SendAt { get; set; }
    public DateTime? SeenAt { get; set; }
    public string Text { get; set; } = null!;
    public int SenderId { get; set; }
    public int ChatroomId { get; set; }

    [JsonIgnore]
    public virtual Chatroom? Chatroom { get; set; } = null!;
    [JsonIgnore]
    public virtual User? Sender { get; set; } = null!;
}
