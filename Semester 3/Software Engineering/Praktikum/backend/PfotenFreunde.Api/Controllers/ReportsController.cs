using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Api.Extensions;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class ReportsController : ControllerBase
{
	private PfotenFreundeContext context;

	public ReportsController(PfotenFreundeContext context)
	{
		this.context = context;
	}
	
    /// <summary>
    /// Gets all open reports
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    [HttpGet]
    public ActionResult<IEnumerable<Report>> GetAll()
    {
        if (!this.IsAdministrator())
        {
            return Forbid();
        }

        return Ok(context.Reports.Where(x => x.State == ReportState.Open));
    }

    /// <summary>
    /// Set report state
    /// </summary>
    [HttpDelete("{id}/state")]
    public async Task<ActionResult> PostState(int id, ReportState state)
    {
        if (!this.IsAdministrator())
        {
            return Forbid();
        }

        var report = await context.Reports.FindAsync(id);
        if (report == null)
        {
            return NotFound();
        }

        report.State = state;

        context.Reports.Update(report);
        await context.SaveChangesAsync();

        return Ok();
    }

    /// <summary>
    /// Deletes a report
    /// </summary>
    [HttpDelete("{id}")]
    public async Task<ActionResult> Delete(int id)
    {
        if (!this.IsAdministrator())
        {
            return Forbid();
        }

        var report = await context.Reports.FindAsync(id);
        if (report == null)
        {
            return NotFound();
        }

        context.Reports.Remove(report);
        await context.SaveChangesAsync();

        return Ok();
    }
}
