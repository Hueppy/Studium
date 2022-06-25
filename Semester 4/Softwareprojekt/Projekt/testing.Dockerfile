FROM node:lts

WORKDIR /app

ENV PATH /app/node_modules/.bin:$PATH

COPY Service-Bildungsportal/frontend/package.json .
COPY Service-Bildungsportal/frontend/package-lock.json .
RUN npm install --silent
RUN npm install react-scripts@3.4.1 -g --silent

COPY Service-Bildungsportal/frontend .

# start app
CMD ["npm", "start"]
