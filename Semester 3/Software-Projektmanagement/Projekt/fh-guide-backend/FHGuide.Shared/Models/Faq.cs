using System.Text.Json.Serialization;

namespace FHGuide.Shared.Models;

public partial class Faq
{
    public int FaqId { get; set; }
    public string Question { get; set; } = null!;
    public string? Answer { get; set; }
    public string? Categorie { get; set; }
    public int AccountId { get; set; }
    public int ModuleId { get; set; }

    [JsonIgnore]
    public virtual Account? Account { get; set; } = null!;
    [JsonIgnore]
    public virtual Module? Module { get; set; } = null!;
}
