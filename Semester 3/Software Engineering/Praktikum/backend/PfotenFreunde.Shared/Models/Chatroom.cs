using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Chatroom
{
    public Chatroom()
    {
        Messages = new HashSet<Message>();
        Users = new HashSet<User>();
    }

    public int Id { get; set; }
    public DateTime? StartedAt { get; set; }

    [JsonIgnore]
    public virtual ICollection<Message> Messages { get; set; }

    [JsonIgnore]
    public virtual ICollection<User> Users { get; set; }
}
