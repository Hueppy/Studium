using Microsoft.AspNetCore.Mvc;
using FHGuide.Shared.Models;
using FHGuide.Shared.Contexts;

namespace FHGuide.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class FaqController : ControllerBase
{
	private readonly FHGuideContext DbContext;

    public FaqController(FHGuideContext dbContext)
    {
		this.DbContext = dbContext;
    }

	/// <summary>
	/// Get all Faq
	/// </summary>
	[HttpGet]
	public IEnumerable<Faq> Get()
	{
		return this.DbContext.Faqs;
	}

	/// <summary>
	/// Add a question to Faq
	/// </summary>
	[HttpPost]
	public async Task<int> Post(Faq faq)
	{
		faq.FaqId = 0;
        var entry = await this.DbContext.Faqs.AddAsync(faq);
        await this.DbContext.SaveChangesAsync();
        return entry.Entity.FaqId;
	}

	/// <summary>
	/// Update question with specified id
	/// </summary>
	[HttpPatch("{id}")]
	public async Task<ActionResult> Patch(int id, Faq faq)
	{
		if (!this.DbContext.Faqs.Any(x => x.FaqId == id)) {
            return NotFound();
        }
        faq.FaqId = id;
        var entry = this.DbContext.Faqs.Update(faq);
        await this.DbContext.SaveChangesAsync();
        return Ok();
	}

	/// <summary>
	/// Delete question with specified id
	/// </summary>
	[HttpDelete("{id}")]
	public async Task<ActionResult> Delete(int id)
	{
		var faq = await this.DbContext.Faqs.FindAsync(id);
        if (faq == null)
        {
            return NotFound();
        }    
        
        this.DbContext.Faqs.Remove(faq);
        await this.DbContext.SaveChangesAsync();
        return Ok();
	}
}
