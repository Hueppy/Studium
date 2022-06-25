
import pika
import os

connection = pika.BlockingConnection(
    pika.ConnectionParameters(
        host=os.environ['RABBITMQ_HOST'],
        port=int(os.environ['RABBITMQ_PORT']),
        credentials=pika.credentials.PlainCredentials(os.environ['RABBITMQ_USER'], os.environ['RABBITMQ_PASSWORD'])))
channel = connection.channel()

channel.exchange_declare(exchange=os.environ['RABBITMQ_EXCHANGE'], exchange_type='topic', durable=True)

result = channel.queue_declare('', exclusive=True)
queue_name = result.method.queue

channel.queue_bind(
        exchange=os.environ['RABBITMQ_EXCHANGE'], queue=queue_name, routing_key='service.hello')


def callback(ch, method, properties, body):
    channel.basic_publish(
        exchange=os.environ['RABBITMQ_EXCHANGE'], routing_key='service.world', body=os.environ['PAYLOAD_SECRET'])


channel.basic_consume(
    queue=queue_name, on_message_callback=callback, auto_ack=True)

channel.start_consuming()

connection.close()
