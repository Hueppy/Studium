using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Login
{
    public string Email { get; set; } = null!;
    public string PasswordHash { get; set; } = null!;
    public Role Role { get; set; }

    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
