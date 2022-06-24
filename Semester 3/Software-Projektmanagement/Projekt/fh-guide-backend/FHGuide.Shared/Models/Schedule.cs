using System.Text.Json.Serialization;

namespace FHGuide.Shared.Models;

public partial class Schedule
{
    public int ScheduleId { get; set; }
    public DateTime? ExpireDate { get; set; }
    public DateTime CreateDate { get; set; }
    public int AccountId { get; set; }

    [JsonIgnore]
    public virtual Account? Account { get; set; } = null!;
}
