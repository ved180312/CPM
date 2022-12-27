# frozen_string_literal: true

require 'stripe'

# frozen_string_literal: true

# strip service
class StripeService
  def initialize
    Stripe.api_key = ENV['STRIPE_SECRET_KEY']
  end
end
