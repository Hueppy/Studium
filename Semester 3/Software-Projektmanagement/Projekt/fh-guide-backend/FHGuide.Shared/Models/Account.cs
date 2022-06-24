using System.Text.Json.Serialization;

namespace FHGuide.Shared.Models;

public partial class Account
{
    public Account()
    {
        Faqs = new HashSet<Faq>();
        Ratings = new HashSet<Rating>();
        Schedules = new HashSet<Schedule>();
    }

    public int AccountId { get; set; }
    public string Username { get; set; } = null!;
    public string Email { get; set; } = null!;
    public string Password { get; set; } = null!;
    public DateTime CreateDate { get; set; }

    [JsonIgnore]
    public virtual ICollection<Faq> Faqs { get; set; }
    [JsonIgnore]
    public virtual ICollection<Rating> Ratings { get; set; }
    [JsonIgnore]
    public virtual ICollection<Schedule> Schedules { get; set; }
}
