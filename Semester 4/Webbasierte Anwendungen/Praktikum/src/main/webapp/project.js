function doCommentSubmit(event) {
    event.preventDefault()

    const comment = document.getElementById('comment')
    localStorage.setItem('comment', comment.value)
    const lastComment = document.getElementById('lastcomment');
    lastComment.innerHTML = comment.value
}

window.addEventListener('load', async function () {
    const id = new URL(window.location.href).searchParams.get('id')

    if (id) {
        const api = new ProjectApi()
        const project = await api.single(id)

        const title = document.getElementById('title')
        title.innerHTML = project.title
        const shortDescription = document.getElementById('short_description_text')
        shortDescription.innerHTML = project.shortDescription
        const longDescription = document.getElementById('long_description_text')
        longDescription.innerHTML = project.longDescription

        let counter = 0
        let toc = document.getElementById('toc_description')
        for (const child of longDescription.childNodes) {
            if (child.tagName && child.tagName.startsWith('H')) {
                child.id = `desc-${counter}`
                const entry = document.createElement(child.tagName);
                entry.innerHTML = `<a href="#${child.id}">${child.innerHTML}</a>`
                toc.append(entry)
                counter++
            }
        }
    }

    const form = document.getElementById('commentform');
    form.addEventListener('submit', doCommentSubmit);

    const lastComment = document.getElementById('lastcomment');
    lastComment.innerHTML = localStorage.getItem('comment')
})