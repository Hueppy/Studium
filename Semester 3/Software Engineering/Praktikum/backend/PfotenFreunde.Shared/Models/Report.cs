using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Report
{
    public int Id { get; set; }
    public string Comment { get; set; } = null!;
    public ReportType Type { get; set; }
    public ReportState State { get; set; }
    public DateTime SendAt { get; set; }
    public DateTime UpdatedAt { get; set; }
    public int UserId { get; set; }
    public int SenderId { get; set; }

    [JsonIgnore]
    public virtual User Sender { get; set; } = null!;
    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
